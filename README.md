Reflection on the Project

What problem was I solving?

I needed to create an advising tool that lets faculty quickly look up CS courses, see how they fit together, and answer student questions. The core requirements boiled down to loading structured data, searching it efficiently, and presenting it in a human‑friendly way.

How did I approach it, and why do data structures matter?

I began by defining a minimal Course model—number, title, prerequisites—and then chose an ordered map (std::map) as the primary container.  A map gives me O(log n) inserts/look‑ups and guarantees that an in‑order traversal prints courses alphabetically, so I get sorting "for free."  This small design decision (data‑structure before algorithm) eliminated the need for an explicit sort step and simplified the code.

Roadblocks and how I overcame them

Parsing quirks – CSV lines occasionally had stray spaces; a tiny trim() helper cleaned them up.

CLion build errors – Deleting the template main.cpp broke the default CMake target.  Updating CMakeLists.txt to point at the new file fixed it instantly.

File‑path issues – The program originally couldn’t find the CSV when run from CLion’s build directory.  Copying the file next to the executable or using a relative path solved that, and I later added whitespace‑trimming to tolerate accidental spaces in the filename.

How the project expanded my design mindset

Working end‑to‑end—parsing, data modeling, UI loop—reinforced the value of small, single‑purpose functions and clear separation between I/O and business logic. It also reminded me that the simplest data structure that meets the performance target is usually the right one; I almost over‑engineered with a custom BST before realizing std::map already matched every requirement.

How my coding style evolved

I leaned on speaking function names, top‑of‑file comments, and early input validation to make the program readable for future me (or classmates).  By isolating trim/normalization utilities and keeping main() nearly narrative, the code is now easier to extend—e.g., adding JSON export would touch only one extra function.  These habits all push the project toward being maintainable, testable, and adaptable well beyond its initial assignment scope.
