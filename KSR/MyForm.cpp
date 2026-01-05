#include <tchar.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

// Структура для хранения информации о книге
public ref class Book {
public:
    String^ Author;
    String^ Title;
    DateTime PublicationDate;

    Book(String^ author, String^ title, DateTime publicationDate) {
        Author = author;
        Title = title;
        PublicationDate = publicationDate;
    }
};

// Класс формы
public ref class MainForm : public Form {
private:
    DataGridView^ dataGridView;
    Button^ sortButton;
    ComboBox^ sortComboBox;
    System::Collections::Generic::List<Book^>^ books;

public:
    MainForm() {
        InitializeComponent();
    }

private:
    void InitializeComponent() {
        this->Text = L"Book Sorter";
        this->Size = System::Drawing::Size(500, 400);

        // Инициализация DataGridView
        dataGridView = gcnew DataGridView();
        dataGridView->Size = System::Drawing::Size(400, 250);
        dataGridView->Location = Point(30, 30);
        dataGridView->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
        dataGridView->Columns->Add("Author", "Author");
        dataGridView->Columns->Add("Title", "Title");
        dataGridView->Columns->Add("PublicationDate", "Publication Date");
        this->Controls->Add(dataGridView);

        // Инициализация ComboBox для выбора критерия сортировки
        sortComboBox = gcnew ComboBox();
        sortComboBox->Location = Point(30, 300);
        sortComboBox->Size = System::Drawing::Size(150, 20);
        sortComboBox->Items->AddRange(gcnew array<String^> { "Author", "Title", "PublicationDate" });
        sortComboBox->SelectedIndex = 0;
        this->Controls->Add(sortComboBox);

        // Инициализация кнопки сортировки
        sortButton = gcnew Button();
        sortButton->Location = Point(200, 300);
        sortButton->Size = System::Drawing::Size(100, 30);
        sortButton->Text = L"Sort";
        sortButton->Click += gcnew EventHandler(this, &MainForm::SortButton_Click);
        this->Controls->Add(sortButton);

        // Инициализация списка книг
        books = gcnew System::Collections::Generic::List<Book^>();
        books->Add(gcnew Book("Leo Tolstoy", "War and Peace", DateTime(1869, 1, 1)));
        books->Add(gcnew Book("Fyodor Dostoevsky", "Crime and Punishment", DateTime(1866, 1, 1)));
        books->Add(gcnew Book("George Orwell", "1984", DateTime(1949, 6, 8)));
        books->Add(gcnew Book("J.K. Rowling", "Harry Potter and the Philosopher's Stone", DateTime(1997, 6, 26)));

        // Заполнение DataGridView данными
        UpdateDataGridView();
    }

    void UpdateDataGridView() {
        dataGridView->Rows->Clear();
        for each (Book ^ book in books) {
            dataGridView->Rows->Add(book->Author, book->Title, book->PublicationDate.ToShortDateString());
        }
    }

    // Метод для сравнения по автору
    static int CompareByAuthor(Book^ a, Book^ b) {
        return String::Compare(a->Author, b->Author);
    }

    // Метод для сравнения по названию
    static int CompareByTitle(Book^ a, Book^ b) {
        return String::Compare(a->Title, b->Title);
    }

    // Метод для сравнения по дате издания
    static int CompareByPublicationDate(Book^ a, Book^ b) {
        return DateTime::Compare(a->PublicationDate, b->PublicationDate);
    }

    void SortButton_Click(Object^ sender, EventArgs^ e) {
        String^ sortBy = sortComboBox->SelectedItem->ToString();

        if (sortBy == "Author") {
            books->Sort(gcnew Comparison<Book^>(&MainForm::CompareByAuthor));
        }
        else if (sortBy == "Title") {
            books->Sort(gcnew Comparison<Book^>(&MainForm::CompareByTitle));
        }
        else if (sortBy == "PublicationDate") {
            books->Sort(gcnew Comparison<Book^>(&MainForm::CompareByPublicationDate));
        }

        UpdateDataGridView();
    }
};

[STAThread]
int main() {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew MainForm());
    return 0;
}