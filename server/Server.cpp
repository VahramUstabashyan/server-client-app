#include "Server.hpp"

Server::Server(const std::string& ip, int port)
        : acceptor(io_context,
                   tcp::endpoint(boost::asio::ip::make_address(ip), port)),
          num_clients(0) {
    async_accept();
    io_thread = std::thread([this]() {
        io_context.run();
    });
}

Server::~Server() {
    if (io_thread.joinable()) {
        io_context.stop();
        io_thread.join();
    }
}

void Server::async_accept() {
    acceptor.async_accept([this](boost::system::error_code err,
                                 tcp::socket socket) {
        handle_connection(err, std::move(socket));
    });
}

void Server::handle_connection(boost::system::error_code err,
                               tcp::socket socket) {
    if (!err) {
        std::cout << "Connection request" << std::endl;

        auto client = std::make_unique<Connection>(std::make_unique<tcp::socket>(std::move(socket)));
        if (num_clients < max_clients) {
            auto remote_ip_port = client->remote_ip_port();
            client->set_observer(weak_from_this());
            client->read();
            clients[remote_ip_port] = std::move(client);
            ++num_clients;
            std::cout << "Client " << remote_ip_port << " successfully added!" << std::endl;
        } else {
            std::cout << "Failed to add client: maximum number of clients reached (" << max_clients << ")" << std::endl;
            client->writeln("Maximum number of clients reached. Connection rejected.");
            client->close();
        }
    }
    async_accept();
}

std::string Server::handle_new_message(std::string msg, const std::string& ip_port) {
    if (msg == "disconnect") {
        disconnect(ip_port);
        std::cout << "Successfully disconnected from client " << ip_port << std::endl;
        return {};
    } else {
        if (p_threads.find(ip_port) == p_threads.end()) p_threads[ip_port] = std::vector<std::thread>();
        auto nt = std::thread([this, msg, ip_port]() {
            shell(msg, ip_port);
            });
        p_threads[ip_port].push_back(std::move(nt));
        return "";
    }
}

void Server::disconnect(const std::string& ip_port) {
    for (auto pid: pids[ip_port]) {
        // Kill not finished processes with all their child processes
        system(("pkill -INT -P" + std::to_string(pid)).c_str());
    }
    for (auto& t: p_threads[ip_port]) {
        if (t.joinable()) t.join();
    }
    clients[ip_port]->close();
    pids.erase(ip_port);
    p_threads.erase(ip_port);
    clients.erase(ip_port);
    --num_clients;
}

#define READ 0
#define WRITE 1
std::string Server::shell(const std::string& command, const std::string& ip_port) {
    std::cout << "Running command from " << ip_port << ": " << command << std::endl;

    int p_stdout[2];
    pipe(p_stdout);
    pid_t pid = fork();
    if (pid < 0) {
        std::cout << "Error on execvp" << std::endl;
    } else if (pid == 0) {
        close(p_stdout[READ]);
        dup2(p_stdout[WRITE], WRITE);
        execlp("/bin/sh", "/bin/sh", "-c", command.c_str(), nullptr);
        perror("execlp");
        exit(1);
    }

    if (pids.find(ip_port) == pids.end()) pids[ip_port] = {};
    pids[ip_port].push_back(pid);

    close(p_stdout[WRITE]);
    FILE* fp_stdout = fdopen(p_stdout[READ], "r");

    std::array<char, 128> buffer{};
    while (fgets(buffer.data(), buffer.size(), fp_stdout) != nullptr) {
        clients[ip_port]->writeln(buffer.data());
    }

    fclose(fp_stdout);
    wait(nullptr);
    pids[ip_port].erase(std::find(pids[ip_port].begin(), pids[ip_port].end(), pid));
    return "";
}
