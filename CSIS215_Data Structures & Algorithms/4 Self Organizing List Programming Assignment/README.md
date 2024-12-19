Implement the three self-organizing list heuristics:
    • Count – Whenever a record is accessed it may move toward the front of the list if its number of accesses becomes greater than the record(s) in front of it.
    • Move-to-front – Whenever a record is accessed it is moved to the front of the list.  This heuristic only works well with linked-lists; because, in arrays the cost of shifting all the records down one spot every time you move a record to the front is too expensive.
    • Transpose – whenever the record is accessed swap it with the record immediately in front of it.