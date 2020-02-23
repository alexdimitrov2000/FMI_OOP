#include <iostream>
using namespace std;

const int BOOK_NAME_LENGTH = 20;
const int AUTHOR_NAME_LENGTH = 20;
const int GENRE_NAME_LENGTH = 20;

const int BOOKS_LENGTH = 20;

struct Book {
	char bookName[BOOK_NAME_LENGTH];
	char authorName[AUTHOR_NAME_LENGTH];
	int isbn;
	char genre[GENRE_NAME_LENGTH];
	double price;
};

struct BookStore {
	int bookCount;
	Book books[BOOKS_LENGTH];
};

int main()
{
	
}