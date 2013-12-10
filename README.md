Cplusplus-Tiled-PathFinding-with-Threads
========================================

Assignmnet using SDL C++ tinyxml for reading TILED maps and path finding

A* star algorithm for path finding, although two simple vector lists are used, priority queue needed for efficiency and more efficient closed list for larger scale problems

Also attempt at threading the enemies
Enemeies themselves run in the main thread, but they're paths are gotten from a separate thread that's sole purpose is to make paths from a start point to a goal
Cost path terrain implemented
