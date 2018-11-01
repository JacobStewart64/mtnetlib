I can see this codebase going places.

I'll leave this here, hope it helps somebody, but I must make this library private and try to sell it lol.

I need to use signals to unblock from epoll_wait but it always ruins my program. The grand idea is to be able to reconfigure without down time, run analysis of throughput and whatnot, and change configuration to find the sweet spot automatically. The more metrics I can vary to change results the better. Even a random configurator could eventually roughly find the sweet spot!