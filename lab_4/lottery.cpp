// Author: Jake Tuero
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>

struct Job {
    Job(int _tickets)
        : tickets(_tickets) {}
    int tickets;
};

struct JobManager {
    void add_job(int num_tickets) {
        jobs.emplace_back(num_tickets);
        stats.push_back(0);
        total_tickets += num_tickets;
    }

    void schedule_job() {
        assert(total_tickets > 0);
        int winner = rand() % total_tickets;    // get winner
        int current = 0;
        std::size_t winner_idx{};
        for (winner_idx = 0; winner_idx < jobs.size(); ++winner_idx) {
            current += jobs.at(winner_idx).tickets;
            if (current > winner) {
                break;
            }
        }
        // print winnner
        std::cout << "winner: " << winner << " -> job " << winner_idx << std::endl;
        ++stats.at(winner_idx);
    }

    void print_stats() {
        int total_time_share = std::reduce(stats.begin(), stats.end());
        std::cout << "Summary statistics" << std::endl;
        for (std::size_t i = 0; i < jobs.size(); ++i) {
            int tickets = jobs.at(i).tickets;
            double ticket_share_percentage = static_cast<double>(tickets) / total_tickets;
            double time_share_percentage = static_cast<double>(stats.at(i)) / total_time_share;
            printf(
                "Job %d, tickets: %d, percentage of tickets: %.2f, percentage of time share: %.2f\n",
                static_cast<int>(i),
                tickets,
                ticket_share_percentage,
                time_share_percentage
            );
        }
    }

    int total_tickets = 0;
    std::vector<Job> jobs;
    std::vector<int> stats;
};

int main(int argc, char *argv[]) {
    if (argc < 4) {
        std::cerr << "usage: lottery <seed> <loops> <job1> <job2> ... <jobN>" << std::endl;
        exit(1);
    }
    int seed = atoi(argv[1]);
    int loops = atoi(argv[2]);

    // Initialize our jobs
    JobManager manager;
    for (int i = 3; i < argc; ++i) {
        int job_tickets = atoi(argv[i]);
        if (job_tickets < 0) {
            std::cerr << "Expected job tickets to be a positive number" << std::endl;
            return 1;
        }

        manager.add_job(job_tickets);
    }

    // Initialize our source of randomness
    srandom(static_cast<unsigned int>(seed));

    // Simulate
    for (int i = 0; i < loops; ++i) {
        manager.schedule_job();
    }

    // print stats
    manager.print_stats();

    return 0;
}
