# AvanceradC++.Lab.01
This is a doubly linked list that is made as a assignment for the course advanced programming in c++
The idéa is to make a DLL using templates(or rather CRTP)
How does it work?
Basically the magic happends in the link template, it handles all operations that are done in the DLL. The list is derived from links and
just like every link it holds a next and a prev pointer, you can consider this "link" to be both the head and the tail of the list. This
means that the lists next pointer will point to the first link in the list and the prev pointer to the last.
