# ?? Browser History Simulator — C++ DSA Project

> A console-based browser history simulator built in **C++**, demonstrating the power of **Doubly Linked Lists** to replicate back/forward navigation — just like a real web browser!

---

## ?? Table of Contents

- [Overview](#-overview)
- [Core Concept — Doubly Linked List](#-core-concept--doubly-linked-list)
- [Data Structure Design](#-data-structure-design)
- [Class & Method Breakdown](#-class--method-breakdown)
- [How It Works — Step by Step](#-how-it-works--step-by-step)
- [Menu & User Interaction](#-menu--user-interaction)
- [Sample Output](#-sample-output)
- [Key DSA Concepts Used](#-key-dsa-concepts-used)
- [Time & Space Complexity](#-time--space-complexity)
- [How to Compile & Run](#-how-to-compile--run)
- [Project Structure](#-project-structure)
- [Learning Outcomes](#-learning-outcomes)

---

## ?? Overview

This project simulates the **browser navigation history** feature (Back / Forward / Visit) using a **Doubly Linked List** in C++.

When you browse the internet:
- Every new page you visit gets added to a history chain.
- You can go **back** to the previous page.
- You can go **forward** to the next page.
- If you visit a new URL while in the middle of history, all **forward history is cleared** — exactly like real browsers do.

This project replicates all of the above behaviors from scratch using fundamental DSA concepts.

---

## ?? Core Concept — Doubly Linked List

A **Doubly Linked List** is a linear data structure where each node holds:
- **Data** — the URL of a page
- **`next` pointer** — points to the next (forward) page
- **`prev` pointer** — points to the previous (back) page

```
NULL <- [Google.com] <-> [Youtube.com] <-> [GitHub.com] -> NULL
                               ^
                         CurrentPage
```

This bi-directional linking is what makes **back and forward navigation** possible in O(1) time.

---

## ??? Data Structure Design

### `struct node`

```cpp
struct node {
    string url;       // Stores the URL of the webpage
    node *next;       // Pointer to the next (forward) page
    node *prev;       // Pointer to the previous (back) page

    node(string u) {
        url  = u;
        next = NULL;
        prev = NULL;
    }
};
```

Each `node` represents **one webpage** in the browser history. The constructor initializes the URL and sets both pointers to `NULL` (isolating the node by default).

---

## ?? Class & Method Breakdown

### `class BrowserHistory`

The entire browser simulation lives inside this class. It has a single private member:

| Member | Type | Purpose |
|---|---|---|
| `CurrentPage` | `node*` | Always points to the page the user is currently on |

---

### Methods

#### 1. `BrowserHistory(string homepage)` — Constructor

```cpp
BrowserHistory(string homepage) {
    CurrentPage = new node(homepage);
    cout << "\nBrowser Started at : " << CurrentPage->url << endl;
}
```

- **Purpose:** Initializes the browser with a starting homepage (defaults to `"Google.com"`).
- **Action:** Allocates a new `node` on the heap and sets `CurrentPage` to it.
- **Effect:** The browser opens with the homepage loaded.

---

#### 2. `void visit(string url)` — Visit a New Page

```cpp
void visit(string url) {
    // Step 1: Save reference to current forward history
    node *temp = CurrentPage->next;

    // Step 2: Delete all forward nodes (clears forward history)
    while (temp != NULL) {
        node *nextnode = temp->next;
        delete temp;
        temp = nextnode;
    }

    // Step 3: Create new node for visited URL
    node *newnode = new node(url);

    // Step 4: Link new node to current page
    CurrentPage->next = newnode;
    newnode->prev     = CurrentPage;

    // Step 5: Move CurrentPage forward to new node
    CurrentPage = newnode;

    cout << "Visited : " << CurrentPage->url << endl;
}
```

- **Purpose:** Navigate to a new URL.
- **Key Behavior:** If the user was in the middle of history (had gone back), visiting a new page **clears all forward history** before adding the new page. This matches how Chrome, Firefox, etc. behave.

**Visualization:**

```
Before visit (user went back):
[Google] <-> [YouTube] <-> [GitHub]
               ^
         CurrentPage

After visit("Twitter.com"):
[Google] <-> [YouTube] <-> [Twitter]   (GitHub node is deleted)
                               ^
                         CurrentPage
```

---

#### 3. `void back()` — Go to Previous Page

```cpp
void back() {
    if (CurrentPage->prev != NULL) {
        CurrentPage = CurrentPage->prev;
        cout << "Back at the page : " << CurrentPage->url << endl;
    } else {
        cout << "No previous Page Found" << endl;
    }
}
```

- **Purpose:** Move one step backward in history.
- **Guard:** Checks if `prev` is `NULL` (i.e., we are already at the first page). If so, prints a message instead of crashing.
- **Action:** Simply moves the `CurrentPage` pointer one node to the left.

---

#### 4. `void forward()` — Go to Next Page

```cpp
void forward() {
    if (CurrentPage->next != NULL) {
        CurrentPage = CurrentPage->next;
        cout << "Forwarded to next Page : " << CurrentPage->url << endl;
    } else {
        cout << "No Page found" << endl;
    }
}
```

- **Purpose:** Move one step forward in history.
- **Guard:** Checks if `next` is `NULL` (i.e., we are at the most recent page). If so, prints a message.
- **Action:** Simply moves the `CurrentPage` pointer one node to the right.

---

#### 5. `void viewpages()` — Display All Pages

```cpp
void viewpages() {
    node *ptr = CurrentPage;

    // Step 1: Rewind to the very first page (head)
    while (ptr->prev != NULL)
        ptr = ptr->prev;

    // Step 2: Print all pages, marking the current one
    while (ptr != NULL) {
        if (ptr == CurrentPage)
            cout << " --> " << ptr->url << endl;  // Indicates current page
        else
            cout << "     " << ptr->url << endl;
        ptr = ptr->next;
    }
}
```

- **Purpose:** Print the complete history list, with `-->` indicating which page is currently active.
- **How:** First rewinds to the head (first node), then traverses forward printing all URLs.

**Example output:**

```
     Google.com
     Youtube.com
 --> GitHub.com
     Twitter.com
```

---

## How It Works — Step by Step

```
1. Browser launches -> CurrentPage = Google.com

2. User visits YouTube.com
   Google.com <-> YouTube.com
                     ^ CurrentPage

3. User visits GitHub.com
   Google.com <-> YouTube.com <-> GitHub.com
                                      ^ CurrentPage

4. User presses BACK twice
   Google.com <-> YouTube.com <-> GitHub.com
       ^ CurrentPage

5. User visits Twitter.com (new visit while in history)
   GitHub.com is DELETED (forward history cleared)
   Google.com <-> Twitter.com
                      ^ CurrentPage
```

---

## Menu & User Interaction

The `main()` function runs a **do-while loop** presenting a menu until the user chooses to exit:

```
------------------------------------
0. Exit
1. Visit Site
2. Previous Tab (Back)
3. Next Tab (Forward)
4. View Pages
------------------------------------
Choice:
```

| Choice | Action |
|---|---|
| `0` | Exits the program |
| `1` | Prompts for a URL and visits it |
| `2` | Goes back one page |
| `3` | Goes forward one page |
| `4` | Displays all pages in history |

---

## Sample Output

```
Browser Started at : Google.com

------------------------------------
0.Exit
1.Visit Site.
2.Previous Tab.
3.Next Tab.
4.View Pages.
------------------------------------
Choice: 1

Enter Url: YouTube.com
Visited : YouTube.com

Choice: 1

Enter Url: GitHub.com
Visited : GitHub.com

Choice: 2
Back at the page : YouTube.com

Choice: 4
     Google.com
 --> YouTube.com
     GitHub.com

Choice: 1

Enter Url: Twitter.com
Visited : Twitter.com

Choice: 4
     Google.com
     YouTube.com
 --> Twitter.com

Choice: 0

exited successfully
```

---

## Key DSA Concepts Used

| Concept | Where Used |
|---|---|
| **Doubly Linked List** | Core data structure for history chain |
| **Dynamic Memory Allocation** | `new` and `delete` for heap-allocated nodes |
| **Pointer Manipulation** | Traversal, linking, and unlinking nodes |
| **Memory Management** | Forward history nodes deleted on `visit()` |
| **OOP (Classes & Objects)** | `BrowserHistory` class encapsulates all logic |
| **do-while loop** | Menu keeps running until user exits |
| **switch-case** | Routes user choice to correct action |

---

## Time & Space Complexity

| Operation | Time Complexity | Explanation |
|---|---|---|
| `visit(url)` | O(n) worst case | Must delete all forward history nodes |
| `back()` | O(1) | Just move pointer one step left |
| `forward()` | O(1) | Just move pointer one step right |
| `viewpages()` | O(n) | Must rewind to head, then traverse all nodes |

| Resource | Space Complexity |
|---|---|
| History storage | O(n) — one node per page visited |
| Pointers | O(1) per node (constant overhead) |

---

## How to Compile & Run

### Prerequisites
- A C++ compiler: `g++` (GCC), `clang++`, or MSVC
- Terminal / Command Prompt

### Compile

```bash
g++ Browser_History.cpp -o Browser_History
```

### Run

**Linux / macOS:**
```bash
./Browser_History
```

**Windows:**
```bash
Browser_History.exe
```

---

## Project Structure

```
Project's/
|
|-- Browser_History.cpp   # Main source file
|-- Browser_History.exe   # Compiled Windows executable
+-- README.md             # This documentation file
```

---

## Learning Outcomes

By studying and running this project, you will understand:

1. How **Doubly Linked Lists** work with `prev` and `next` pointers
2. Why real browsers clear forward history on a new visit
3. How **dynamic memory allocation** (`new`/`delete`) works in C++
4. How to design a class that encapsulates a linked list
5. How real-world browser navigation maps directly to a DSA concept
6. Pointer arithmetic and safe traversal with NULL checks

---

## Author

**LPU Summer Training — DSA Project**  
*Data Structures & Algorithms with C++*

---

## License

This project is open source and available for educational purposes.

---

> Tip: Try extending this project by adding a `bookmarks` feature, a `search in history` function, or limiting history to the last N pages!
