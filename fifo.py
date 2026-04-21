from collections import deque

def fifo_page_replacement_queue(pages, capacity):
    # Defensive check
    if capacity == 0:
        return len(pages)

    memory_set = set()      # Used for fast O(1) lookups
    memory_queue = deque()  # Used for fast O(1) FIFO ordering
    page_faults = 0

    for page in pages:
        if page not in memory_set:
            # Page Fault occurs
            page_faults += 1
            
            # If memory is full, remove the oldest page (front of the queue)
            if len(memory_queue) == capacity:
                oldest_page = memory_queue.popleft()
                memory_set.remove(oldest_page)
            
            # Add the new page (back of the queue)
            memory_queue.append(page)
            memory_set.add(page)
            
        # Display the current state of the queue as a standard list
        print(f"Page: {page} -> Memory: {list(memory_queue)}")

    print("\nTotal Page Faults:", page_faults)
    return page_faults

# Example input
pages = [1, 2, 3, 1, 4, 5]
capacity = 3

fifo_page_replacement_queue(pages, capacity)def fifo_page_replacement(pages, capacity):
    memory = []
    page_faults = 0
    index = 0  # points to the page to be replaced

    for page in pages:
        if page not in memory:
            page_faults += 1

            if len(memory) < capacity:
                memory.append(page)
            else:
                memory[index] = page
                index = (index + 1) % capacity

        print(f"Page: {page} -> Memory: {memory}")

    print("Total Page Faults:", page_faults)


# Example input
pages = [1, 2, 3, 1, 4, 5]
capacity = 3

fifo_page_replacement(pages, capacity)
