#include "bookui.h"
#include "ui_bookui.h"
#include "algorithms.h"
#include "bookinformation.h"

bookUI::bookUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::bookUI)
{
    ui->setupUi(this);
    ui->booksTree->setHeaderHidden(true);
    addData();
}

bookUI::~bookUI()
{
    delete ui;
}

void bookUI::addRootGenre(QString name)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->booksTree);
    item->setText(0, name);
    ui->booksTree->addTopLevelItem(item);
}

void bookUI::addChildBook(Book* book)
{
    //trying to find the genre of the book from the list
    for( int i = 0; i < ui->booksTree->topLevelItemCount(); ++i )
    {
       QTreeWidgetItem *item = ui->booksTree->topLevelItem(i);
       if (item->text(0) == QString::fromStdString(book->getGenre())){
           QTreeWidgetItem *newBook = new QTreeWidgetItem();
           newBook->setText(0, QString::fromStdString(book->getName()));
           item->addChild(newBook);
           break;
       }
    }
}

void bookUI::addData()
{
    Author *author1 = new Author("Cris Smith", "Classic");
    Author *author2 = new Author("Albert Tuna", "History");
    Author *author3 = new Author("Nickolas Tame", "History");
    Author *author4 = new Author("Khristina Palson", "Thriller");
    Author *author5 = new Author("John Kenner", "Science Fiction");
    authors.push_back(author1);
    authors.push_back(author2);
    authors.push_back(author3);
    authors.push_back(author4);
    authors.push_back(author5);
    authorBookData *data1 = new oneAuthor(author4, "Kelly");
    std::vector<author_pseudonym> many1;
    many1.push_back(author_pseudonym(author1, "Derek"));
    many1.push_back(author_pseudonym(author2, "Felly"));
    many1.push_back(author_pseudonym(author3, "Dams"));
    many1.push_back(author_pseudonym(author5, "Parkinson"));
    authorBookData *data2 = new manyAuthors(many1);
    algorithms algorithm;
    Book *first = new Book("Garry", algorithm.getTime("2000/02/01 00:00:00"), "Classic", 123, data2);
    Book *second = new Book("July moon", algorithm.getTime("2005/02/07 00:00:00"), "History", 123, data1);
    books.push_back(first);
    books.push_back(second);
    addRootGenre("Classic");
    addRootGenre("History");
    addRootGenre("Thriller");
    addRootGenre("Science fiction");
    addRootGenre("Classic");
    for (Book *book : books) addChildBook(book);
}



void bookUI::on_booksTree_itemClicked(QTreeWidgetItem *item, int column)
{
    if (item->parent()){
        Book* searchedBook = books[0];
        for (Book* book : books){
            if (QString::fromStdString(book->getName()) == item->text(0)){
                searchedBook = book;
                break;
            }
        }
        bookinformation = new BookInformation(searchedBook);
        bookinformation->show();
    }
}
