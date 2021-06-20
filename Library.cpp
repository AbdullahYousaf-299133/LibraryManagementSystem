#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;

// Class with supportive functions
class Helper
{
	// A Helper Class With Functions to be used at Multiple points in the cpp
	public:

	static int strlength(char *string)
		{
			//A function to find the length of any given 1D string//
			int length = 0;

			for (char *temp = string; *temp != '\0'; temp++)
			{
				length++;
			}

			return length;
		}

	static char *GetStringFromBuffer(char *buffer)
	{
		//A function that allocates appropriate memory and copies the data from temp buffer to pointer//
		int Length = strlength(buffer);
		char *Char_Pointer = 0;

		if (Length > 0)
		{
			Char_Pointer = new char[Length + 1];
			char *temp_storing = Char_Pointer;
			for (char *temp_copy = buffer; *temp_copy != '\0'; temp_copy++, temp_storing++)
			{*temp_storing = *temp_copy;
			}

			*temp_storing = '\0';
		}

		return Char_Pointer;
	}
	
	static void Deallocating(char ***temp, int stopI)
	{
		// Deallocation 
		if (temp != 0)
		{
			for (int i = 0; i < stopI; i++)
			{
				for (int j = 0;; j++)
				{
					char ch = temp[i][j][0];
					delete[] temp[i][j];
					temp[i][j] = 0;

					if (ch == '-')
					{
						break;
					}
				}

				delete temp[i];
				temp[i] = 0;
			}

			delete[] temp;
			temp = 0;
		}
	}
};

// Class of Books
class Book
{
	private:

	char *Name;
	char *ID;
	char *Type;
	char *Author;
	bool Status;

	public:

	// constructor
	Book()
	{
		Name = nullptr;
		ID = nullptr;
		Type = nullptr;
		Author = nullptr;
		Status = false;
	}

	// Loading Data from File
	void LoadData(ifstream & inp)
	{
		char tempID[100];
		inp >> tempID;
		inp.ignore();
		ID = Helper::GetStringFromBuffer(tempID);

		char tempN[150];
		char ch_N = ' ';
		for (int i = 0; ch_N != '.'; i++)
		{
			inp.get(ch_N);

			if (ch_N != '.')
			{
				tempN[i] = ch_N;
			}
			else
			{
				tempN[i] = '\0';
			}
		}

		Name = Helper::GetStringFromBuffer(tempN);

		char tempT[150];
		inp.ignore();
		char ch_T = ' ';
		for (int i = 0; ch_T != '.'; i++)
		{
			inp.get(ch_T);

			if (ch_T != '.')
			{
				tempT[i] = ch_T;
			}
			else
			{
				tempT[i] = '\0';
			}
		}

		Type = Helper::GetStringFromBuffer(tempT);

		char tempA[150];
		inp.ignore();
		char ch_A = ' ';
		for (int i = 0; ch_A != '.'; i++)
		{
			inp.get(ch_A);

			if (ch_A != '.')
			{
				tempA[i] = ch_A;
			}
			else
			{
				tempA[i] = '\0';
			}
		}

		Author = Helper::GetStringFromBuffer(tempA);

		int s = 0;
		inp >> s;
		if (s == 1)
			Status = true;

		if (s == 0)
			Status = false;

	}

	// Saveing data by writing in file
	void SaveData(ofstream & out)
	{
		out << ID << "\t" << Name << ".\t" << Type << ".\t" << Author << ".\t";
		out << Status;
	}

	// Change availability status of the book
	void ChangeStatus()
	{
		if (Status == false)
		{
			Status = true;
			return;
		}

		if (Status == true)
		{
			Status = false;
			return;
		}
	}

	// Return Avaiability Status of a book
	bool returnStatus()
	{
		return Status;
	}

	// Setters
	void SetName(char *Name_)
	{
		Name = Helper::GetStringFromBuffer(Name_);
	}

	void SetID(char *ID_)
	{
		ID = Helper::GetStringFromBuffer(ID_);
	}

	void SetType(char *Type_)
	{
		Type = Helper::GetStringFromBuffer(Type_);
	}

	void SetAuthor(char *Author_)
	{
		Author = Helper::GetStringFromBuffer(Author_);
	}

	// Getters
	char *GetID()
	{
		return ID;
	}

	char *GetName()
	{
		return Name;
	}

	char *GetType()
	{
		return Type;
	}

	char *GetAuthor()
	{
		return Author;
	}

	// Book Attribute Printing for library
	void BookInfoForLib()
	{
		cout << endl << "ID:\t" << ID << "\t" << "Name:\t"<< Name << "\t\t" << "Type:\t" << Type << "\t\t" << "Author:\t" << Author << "\t";
		if(Status == true)
		{
			cout<< "(Available)"<<endl;
		}
		else
		{
			cout<< "(Unavailable)" <<endl;
		}
	}

	// Book Attribute Printing for Members
	void BookInfoForMem()
	{
		cout << endl << "ID:\t" << ID << "\t" << "Name:\t"<< Name << "\t\t" << "Type:\t" << Type << "\t\t" << "Author:\t" << Author << "\t"<<endl;
	}

	// Destructor
	~Book()
	{
		if (ID != 0)
			delete ID;
			if (Name != 0)
			delete Name;

		if (Type != 0)
			delete Type;
			if (Author != 0)
			delete Author;
	}
};

// Class for Users
class User
{
private:
	char *ID;
	char *firstN;
	char *lastN;
	char *Pass;
	int numberOfBooks;
	Book **assignedBooks;
public:
	// Constructor
	User()
	{
		ID = nullptr;
		firstN = nullptr;
		lastN = nullptr;
		Pass = nullptr;
		numberOfBooks = 0;
		assignedBooks = nullptr;
	}

	// Loading Data From File
	void LoadData(ifstream & inp)
	{
		char tempID[100];
		inp >> tempID;
		ID = Helper::GetStringFromBuffer(tempID);

		char tempFN[100];
		inp >> tempFN;
		firstN = Helper::GetStringFromBuffer(tempFN);

		char tempLN[100];
		inp >> tempLN;
		lastN = Helper::GetStringFromBuffer(tempLN);

		char tempPass[50];
		inp >> tempPass;
		Pass = Helper::GetStringFromBuffer(tempPass);
	}

	// Assigning NEW books
	void AssignBook(Book *NewBook)
	{
		if (numberOfBooks != 0)
		{
			Book **tempBooks = new Book *[numberOfBooks + 1];
			for (int i = 0; i < numberOfBooks; i++)
			{
				tempBooks[i] = assignedBooks[i];
			}

			delete[] assignedBooks;

			tempBooks[numberOfBooks] = NewBook;
			numberOfBooks++;

			assignedBooks = new Book *[numberOfBooks];
			for (int i = 0; i < numberOfBooks; i++)
			{
				assignedBooks[i] = tempBooks[i];
			}

			delete[] tempBooks;
		}
		else
		{
			numberOfBooks++;
			assignedBooks = new Book *[numberOfBooks];

			assignedBooks[0] = NewBook;
		}
	}

	// Getters
	char *GetID()
	{
		return ID;
	}

	// Printing Assigned Books
	void DisplayAssignedBooks()
	{
		if (assignedBooks != nullptr)
		{
			for (int i = 0; i < numberOfBooks; i++)
			{
				assignedBooks[i]->BookInfoForMem();
			}
		}
	}

	// Saving Data By Writing in file
	void SaveData(ofstream & out)
	{
		out << ID << " " << firstN << " " << lastN << " " << Pass;
	}

	// Setting Member Attibutes for the library
	void SetMemberDetails(char *ID_, char *FN_, char *LN_, char *Pass_)
	{
		ID = Helper::GetStringFromBuffer(ID_);
		firstN = Helper::GetStringFromBuffer(FN_);
		lastN = Helper::GetStringFromBuffer(LN_);
		Pass = Helper::GetStringFromBuffer(Pass_);
	}

	// Saving Book info in file
	void SaveBooks(ofstream &OUT)
	{
		if(assignedBooks != nullptr)
		{
			OUT << ID << "\t";
			for(int i = 0; i < numberOfBooks; i++)
			{
				OUT << assignedBooks[i] -> GetID();
				OUT << "\t";
			}
				OUT << "-1" <<endl;
		}
	}

	// Adding new book info
	void AddBook(Book* ADD)
	{

		for(int i = 0; i < numberOfBooks; i++)
		{
			if(assignedBooks[i] == ADD)
			{
				return;
			}
		}
		
		if(numberOfBooks == 0)
		{
			numberOfBooks++;
			assignedBooks = new Book* [numberOfBooks];
			assignedBooks[numberOfBooks - 1] = ADD; 
		}
		else
		{
			Book** Temp;	
			Temp = new Book* [numberOfBooks + 1];
			for(int i = 0; i < numberOfBooks; i++)
			{
				Temp[i] = assignedBooks[i];
			}
			delete[] assignedBooks;

			Temp[numberOfBooks] = ADD;
			numberOfBooks++;

			assignedBooks = new Book*[numberOfBooks];
			for(int i = 0; i < numberOfBooks; i++)
			{
				assignedBooks[i] = Temp[i];
			}
		}
	}

	// Users or librarian Password and username Validity Check
	bool ValidateInfo(char* ID_, char* Pass_)
	{
		bool ID_Check = false;
		bool Pass_Check = false;
		int counter = 0;
		char* ID_T = ID;
		while(*(ID_) != '\0')
		{
			if(*(ID_T) == *(ID_))
			{
				counter++;
			}

			if(counter == Helper::strlength(ID))
			{
				 ID_Check = true;
			}

			ID_T++;
			ID_++;
		}


		counter = 0;
		char* PassT = Pass;
		while(*(Pass_) != '\0')
		{
			if(*(PassT) == *(Pass_))
			{
				counter++;
			}

			if(counter == Helper::strlength(Pass))
			{
				Pass_Check = true;
			}

			PassT++;
			Pass_++;
		}

		if(Pass_Check == true && ID_Check)
		{
			return true;
		}

		return false;
	}

	// Check Book Availability
	bool CheckBook(Book* Check)
	{
		for(int i = 0; i < numberOfBooks; i++)
		{
			if(Check == assignedBooks[i])
			{
				return true;
			}
		}
		return false;
	}

	// Restoring Book Pointer after returning from Members 
	void ReturnBook(Book* Return)
	{
		Book** Temp;
		Temp = new Book* [numberOfBooks];

		for(int i = 0; i < numberOfBooks; i++)
		{
			Temp[i] = assignedBooks[i];
		}
		delete[] assignedBooks;
		numberOfBooks--;
		
		if(numberOfBooks != 0)
		{
			assignedBooks = new Book* [numberOfBooks-1];
			int index  = 0;
			for(int i = 0; i < numberOfBooks; i++)
			{
				if(Temp[i] != Return)
				{
					assignedBooks[index++] = Temp[i];
				}
			}
		}

	}

	// Name And ID Printing
	void ShowDetails()
	{
		cout<<"ID: "<<ID<<endl;
		cout<<"Name: "<<firstN<<" "<<lastN<<endl;
	}

	// Password Changing Functionality
	void ChangePass()
	{
		while(-1)
		{
			system("CLS");
			char Tpass[50];
			cout<<"Enter Current Password (-1 to return): ";
			cin >> Tpass;

			if(Tpass[0] == '-' && Tpass[1] == '1')
			{
				break;
			}

			int counter = 0;
			for(int i = 0; Tpass[i] != '\0'; i++)
			{
				if(Tpass[i] == Pass[i])
				{
					counter++;
				}
			}

			if(counter == Helper::strlength(Pass))
			{
				char Tpass[50];
				cout<<endl<<"Enter New Pass: ";
				cin >> Tpass;
				delete[] Pass;
				Pass = Helper::GetStringFromBuffer(Tpass);
				cout<<endl<<"Succesfully Changed!!"<<endl;
				break;
			}
			else
			{
				cout<<endl<<"Wrong Current Pass"<<endl;

				cout<<"Press any key to try again...";
				_getch();
			}
		}

	}
};

// Class for Library
class Library
{
private:
	User **Record;
	Book **Books;
	int totalMembers;
	int totalBooks;

	// Searching a Book By its ID
	Book* SearchBookByID(char *ID)
	{
		for (int i = 0; i < totalBooks; i++)
		{
			char *TempID = Books[i]->GetID();
			int counter = 0;
			for (int j = 0; ID[j] != '\0'; j++)
			{
				if (ID[j] == TempID[j])
				{
					counter++;
				}

				if (counter == Helper::strlength(ID))
				{
					return Books[i];
				}
			}
		}

		return nullptr;
	}

	// Searching a User By its ID
	User* SearchUserByID(char *ID)
	{

		for (int i = 0; i < totalMembers; i++)
		{
			char *TempID = Record[i] -> GetID();
			int counter = 0;
			for (int j = 0; ID[j] != '\0'; j++)
			{
				if (ID[j] == TempID[j])
				{
					counter++;
				}

				if (counter == Helper::strlength(ID))
				{
					return Record[i];
				}
			}
		}

		return nullptr;
	}

	// Check availbility and return permissions accordingly
	bool GivePermission(Book *Current)
	{
		if (Current->returnStatus() == true)
		{
			return true;
		}

		return false;
	}

public:
	// Constructor
	Library()
	{
		Record = nullptr;
		Books = nullptr;
		totalMembers = 0;
		totalBooks = 0;
	}

	// Loading Data From File
	void LoadBooks()
	{
		ifstream inp("Books.txt");
		inp >> totalBooks;

		if(totalBooks != 0)
		{
			Books = new Book *[totalBooks];
			for (int i = 0; i < totalBooks; i++)
			{
				Books[i] = new Book;
				Books[i]->LoadData(inp);
			}
		}
		else
		{
			cout<<"No Book in the file to Load";
		}
	}

	// Loading Members Information
	void LoadMembers()
	{
		ifstream inp("Members.txt");
		inp >> totalMembers;

		if(totalMembers != 0)
		{
			Record = new User *[totalMembers];

			for (int i = 0; i < totalMembers; i++)
			{
				Record[i] = new User;
				Record[i]->LoadData(inp);
			}
		}
		else
		{
			cout<<endl<<"No members to load"<<endl;
		}
	}

	// Adding or Removing a Particular Book
	void AddOrRemoveBook()
	{
		int choice = 0;
		cout << endl << "Press 1 to add a Book, Press 2 to remove a Book: ";
		cin >> choice;

		if (choice == 1)
		{
			Book **Temp = new Book *[totalBooks + 1];
			for (int i = 0; i < totalBooks; i++)
			{
				Temp[i] = Books[i];
			}

			delete[] Books;

			char tempID[100];
			cout << endl << "Enter the ID of New Book: ";
			cin >> tempID;

			cin.ignore();
			char tempN[150];
			cout << endl << "Enter the Name of New Book: ";
			cin.getline(tempN, 150);

			char tempT[150];
			cout << endl << "Enter the Type of New Book: ";
			cin.getline(tempT, 150);

			char tempA[150];
			cout << endl << "Enter Author name of the New Book: ";
			cin.getline(tempA, 150);

			Temp[totalBooks] = new Book;
			Temp[totalBooks]->SetID(tempID);
			Temp[totalBooks]->SetName(tempN);
			Temp[totalBooks]->SetType(tempT);
			Temp[totalBooks]->SetAuthor(tempA);
			totalBooks++;

			Books = new Book *[totalBooks];

			for (int i = 0; i < totalBooks; i++)
			{
				Books[i] = Temp[i];
			}

			delete[] Temp;
		}

		if (choice == 2)
		{
			char tempID[100];
			cout << endl << "Enter the ID of the Book you want to remove: ";
			cin >> tempID;
			Book *Remove = SearchBookByID(tempID);

			if (Remove != nullptr)
			{
				Book **Temp = new Book *[totalBooks];
				for (int i = 0; i < totalBooks; i++)
				{
					Temp[i] = Books[i];
				}

				delete[] Books;

				Books = new Book *[totalBooks - 1];
				totalBooks--;

				int index = 0;
				for (int i = 0; index < totalBooks; i++)
				{
					if (Temp[i] != Remove)
						Books[index++] = Temp[i];
				}

				delete[] Temp;
				//			delete[] Remove;
			}
			else
			{
				cout << endl << "No such Book found, invalid ID" << endl;
			}
		}
	}

	// Editing a Book's Attributes
	void EditBook()
	{
		cout << endl << "****EDITOR MODE****" << endl;
		char tempID[100];
		cout << endl << "Enter the ID of the Book you want to edit: ";
		cin >> tempID;

		Book *EDIT = SearchBookByID(tempID);

		int choice = 0;
		while (choice != 5)
		{
			system("CLS");
			cout << endl << "Choose what do you want to edit?" << endl;
			cout << "Press 1 for Name, 2 for Type, 3 for Author, 4 for Status, 5 to exit: ";
			cin >> choice;
			cin.ignore();

			if (choice == 1)
			{
				cout<<"Current Name: "<< EDIT -> GetName() << endl;
				char TempN[150];
				cout << endl << "Enter New Name: ";
				cin.getline(TempN, 150);
				EDIT->SetName(Helper::GetStringFromBuffer(TempN));
			}

			if (choice == 2)
			{
				cout<<"Current Type: "<< EDIT -> GetType() << endl;
				char TempT[150];
				cout << endl << "Enter New Type: ";
				cin.getline(TempT, 150);
				EDIT->SetType(Helper::GetStringFromBuffer(TempT));
			}

			if (choice == 3)
			{
				cout<<"Current Author Name: "<< EDIT -> GetAuthor() << endl;
				char TempA[150];
				cout << endl << "Enter New Author Name: ";
				cin.getline(TempA, 150);
				EDIT->SetAuthor(Helper::GetStringFromBuffer(TempA));
			}

			if (choice == 4)
			{
				cout << endl << "Current Status: ";
				if (EDIT->returnStatus())
				{
					cout << "Available";
				}
				else
				{
					cout << "Unavailable";
				}

				int c = 0;
				cout << endl << "Press 1 to change Status, any other number to continue: ";
				cin >> c;

				if (c == 1)
				{
					EDIT->ChangeStatus();
				}
			}
		}
	}

	// Saving a book by writing info to file
	void SaveBooksToFile()
	{
		ofstream OUT("Books.txt");

		OUT << totalBooks << endl;

		for (int i = 0; i < totalBooks; i++)
		{
			Books[i]->SaveData(OUT);
			OUT << endl;
		}
	}

	// Checks book availibilty and deals accordingly
	void BookRequest(char *Book_ID, char *User_ID)
	{
		Book *RequiredBook = SearchBookByID(Book_ID);
		User *CurrentUser = SearchUserByID(User_ID);

		if (RequiredBook != nullptr)
		{
			if (GivePermission(RequiredBook))
			{
				CurrentUser->AssignBook(RequiredBook);
				RequiredBook->ChangeStatus();
			}
			else
			{
				cout << endl << "Book is already issued to another Member" << endl;
			}
		}
		else
		{
			cout << "Unknown ID, Book not Found" << endl;
		}
	}

	// Add a Member into the library system
	void AddMember()
	{
		while (1)
		{
			char tempID[100];
			cout << endl << "Set your ID: ";
			cin >> tempID;

			if(SearchUserByID(tempID) == nullptr)
			{
				cin.ignore();
				char tempFN[150];
				cout << endl << "First Name: ";
				cin.getline(tempFN, 150);

				char tempLN[150];
				cout << endl << "Last Name: ";
				cin.getline(tempLN, 150);

				char tempPass[150];
				cout << endl << "Set your Password: ";
				cin.getline(tempPass, 150);

				User **Temp = new User *[totalMembers + 1];
				for (int i = 0; i < totalMembers; i++)
				{
					Temp[i] = Record[i];
				}

				delete[] Record;

				Temp[totalMembers] = new User;
				Temp[totalMembers]->SetMemberDetails(tempID, tempFN, tempLN, tempPass);
				totalMembers++;

				Record = new User *[totalMembers];

				for (int i = 0; i < totalMembers; i++)
				{
					Record[i] = Temp[i];
				}
				delete[] Temp;
				break;
			}
			else
			{
				cout<<"ID already taken, please select a new ID"<<endl;
			}
		}
	}

	// Remove a Member From the library system
	void RemoveMember()
	{
		char tempID[100];
		cout << endl << "Enter the ID of the Member you want to remove: ";
		cin >> tempID;
		User *Remove = SearchUserByID(tempID);

		if (Remove != nullptr)
		{
			User **Temp = new User *[totalMembers];
			for (int i = 0; i < totalMembers; i++)
			{
				Temp[i] = Record[i];
			}

			delete[] Record;

			Record = new User *[totalMembers - 1];
			totalMembers--;

			int index = 0;
			for (int i = 0; index < totalMembers; i++)
			{
				if (Temp[i] != Remove)
					Record[index++] = Temp[i];
			}

			delete[] Temp;
			//			delete[] Remove;
		}
		else
		{
			cout << endl << "No such member found, invalid ID" << endl;
		}
	}

	// Saving All Members to file
	void SaveMembersToFile()
	{
		ofstream OUT("Members.txt");

		OUT << totalMembers << endl;

		for (int i = 0; i < totalMembers; i++)
		{
			Record[i]->SaveData(OUT);
			OUT << endl;
		}
	}

	// To save books and loading before
	void SaveAllotedBooksWithL()
	{

	/*	ifstream INP ("IssueRecord.txt");
		if(INP)
		{
			cha
		}*/

		LoadAllotedBooks();

		ofstream OUT ("IssueRecord.txt");

		for(int i = 0; i < totalMembers; i++)
		{ 
			Record[i] -> SaveBooks(OUT);
		}
		OUT << "-1";
	}

	// To save Books without Loading
	void SaveAllotedBooksWithoutL()
	{	

		ofstream OUT ("IssueRecord.txt");

		for(int i = 0; i < totalMembers; i++)
		{ 
			Record[i] -> SaveBooks(OUT);
		}
		OUT << "-1";

	}

	// Loading Alloted Books Record
	void LoadAllotedBooks()
	{
		ifstream INP ("IssueRecord.txt");

		if(INP)
		{
			while(1)
			{
				char temp[100];
				INP >> temp;

				if(temp[0] == '-' && temp[1] == '1')
				{
					break;
				}
				User* Current = SearchUserByID(temp);
				if(Current != nullptr)
				{
					while(1)
					{
						char temp2[100];
						INP >> temp2;

						if(temp2[0] == '-' && temp2[1] == '1')
						{
							break;
						}

						Book* ForAdding = SearchBookByID(temp2);
						Current -> AddBook(ForAdding);
					}
				}
				else
				{
					 break;
				}
			}
		}

	}

	// Check library Username and password Validity
	bool ValidateInfo(char* ID, char* Pass)
	{
		User* Current = SearchUserByID(ID);

		if(Current != nullptr)
		{
			if(Current -> ValidateInfo(ID,Pass))
			{
				return true;
			}
		}
		return false;
	}

	// Changing Book Status on being returned from member
	void ReturnABook(char* User_ID)
	{
		User* Check = SearchUserByID(User_ID);
		char tempID[100];
		cout<<"Please enter the ID of the Book you want to return: ";
		cin >> tempID;

		Book* Return = SearchBookByID(tempID);
		if(Check ->	CheckBook(Return))
		{
			Check -> ReturnBook(Return);
			Return -> ChangeStatus();
			cout<<endl<<"Book has been succefully returned"<<endl;
		}
		else
		{
			cout<<endl<<"This Book has not been issued to you, Please enter correct issued Book ID"<<endl;
		}

	}

	// Search and return user by id
	User* ReturnUserByID(char* ID)
	{
		return SearchUserByID(ID);
	}

	// Print Books Information
	void ShowBooks()
	{
		for(int i = 0; i < totalBooks; i++)
		{
			Books[i] -> BookInfoForLib();
		}
	}

	// Print single Member's Information
	void ShowMember(char* ID)
	{
		User* Current = SearchUserByID(ID);
		Current -> ShowDetails();
	}

	// change current user's password
	void ChangePass(char* ID)
	{
		User* Current = SearchUserByID(ID);
		Current -> ChangePass();
	}

	// Print all member's information
	void ShowMembers()
	{
		for(int i = 0; i < totalMembers; i++)
		{
			cout<<endl<<"Member #" <<i+1<<": "<<endl;
			Record[i] ->	 ShowDetails();
		}
	}

	// Search and print member info
	void SearchAndShowMem()
	{
		char t_ID[100];
		cout<<"Enter ID of the Member you want to search: ";
		cin >> t_ID;
		system("CLS");

		User* Current = SearchUserByID(t_ID);
		cout<<"Member Details: "<<endl;
		Current -> ShowDetails();

		cout<<endl<<"Assigned Books: "<<endl;
		Current -> DisplayAssignedBooks();
	}

	// Search and print book info
	void SearchAndShowBook()
	{
		char t_ID[100];
		cout<<"Enter ID of the Member you want to search: ";
		cin >> t_ID;
		system("CLS");

		Book* Current = SearchBookByID(t_ID);
		cout<<"Book Details: "<<endl;
		Current ->BookInfoForLib();
	}
};

// A function with Complete running functionality
void Run()
{
	// Loading all books, alloted books and members
	Library Lib_1;
	Lib_1.LoadBooks();
	Lib_1.LoadMembers();
	Lib_1.LoadAllotedBooks();
	int choice  = 0;

	while(choice != 3)
	{
		// Printing MENU
		system("CLS");
		cout<<"------------------------------ *** MAIN MENU *** ------------------------------"<<endl;
		cout<<endl<<"1- For Librarian \n2- For Member \n3- Exit "<<endl;
		cout<<"\n-------------------------------------------------------------------------------"<<endl;
		cout<<endl<<"Your Choice: ";
		cin >> choice;

		// User's choice
		int inChoice = 0;

		// Librarian interface
		if(choice == 1)
		{
			while(inChoice != 8)
			{
				system("CLS");
				cout<<"----------------------------*** Welcome to Librarian Portal ***----------------------------"<<endl<<endl;
				cout<<endl<<"1- Add Or Remove a Book \n2- Edit a Book \n3- Show All Books \n4- Show All Members \n5- Remove a Member \n6- Search Member by ID \n7- Search Book by ID \n8- Return to Main Menu"<<endl;
				cout<<"\n-------------------------------------------------------------------------------------------"<<endl;
				cout<<endl<<"Your Choice: ";
				cin >> inChoice;

				// Functionalities with their respective choices
				if(inChoice == 1)
				{
					Lib_1.AddOrRemoveBook();
					cout<<endl<<"Press any key to return to Librarian menu...";
					_getch();
				}

				if(inChoice == 2)
				{
					system("CLS");
					Lib_1.EditBook();
					cout<<endl<<"Press any key to return to Librarian menu...";
					_getch();
				}

				if(inChoice == 3)
				{
					system("CLS");
					Lib_1.ShowBooks();
					cout<<endl<<"Press any key to return to Librarian menu...";
					_getch();
				}

				if(inChoice == 4)
				{
					system("CLS");
					Lib_1.ShowMembers();
					cout<<endl<<"Press any key to return to Librarian menu...";
					_getch();
				}

				if(inChoice == 5)
				{
					system("CLS");
					Lib_1.RemoveMember();
					cout<<endl<<"Press any key to return to Librarian menu...";
					_getch();
				}

				if(inChoice == 6)
				{
					system("CLS");
					Lib_1.SearchAndShowMem();
					cout<<endl<<"Press any key to return to Librarian menu...";
					_getch();
				}

				if(inChoice == 7)
				{
					system("CLS");
					Lib_1.SearchAndShowBook();
					cout<<endl<<"Press any key to return to Librarian menu...";
					_getch();
				}

					Lib_1.SaveBooksToFile();
					Lib_1.SaveMembersToFile();
					Lib_1.LoadBooks();
					Lib_1.LoadMembers();
			}
		}

		// Member's Interface
		else if(choice == 2)
		{

			int inChoice = 0;
			while(inChoice != 3)
			{
				system("CLS");
				cout<<"------------------------------- *** Member Options *** -------------------------------"<<endl;
				cout<<endl<<"1- Log In (For existing members) \n2- Sign Up (if you want to become member) \n3- Return to Main Menu"<<endl;
				cout<<"\n-------------------------------------------------------------------------------------"<<endl;
				cout<<endl<<"Your Choice: ";
				cin>>inChoice;

				if(inChoice == 1)
				{
					system("CLS");

					char ID[100];
					cout<<"Enter ID: ";
					cin >> ID;

					char Pass[100];
					cout<<endl<<"Enter Password: ";
					cin >> Pass;

				if(Lib_1.ValidateInfo(ID,Pass))
				{
					int finalChoice = 0;
					while(finalChoice != 7)
					{
						system("CLS");
						cout<<"-------------------------------- *** Welcome to the Member Portal *** --------------------------------"<<endl;
						cout<<endl<<"\t1- Request For a Book \n\t2- Return a Book \n\t3- Your Books \n\t4- Show All Books \n\t5- Your Details \n\t6- Change Password \n\t7- Return to Previous Menu"<<endl;
						cout<<"\n------------------------------------------------------------------------------------------------------"<<endl;
						cout<<endl<<"Your Choice: ";
						cin >> finalChoice;
							if(finalChoice == 1)
							{
								system("CLS");
								char BookID[100];
								cout<<endl<<"Enter ID of the Book you want to request: "<<endl;
								cin >> BookID;
								Lib_1.BookRequest(BookID,ID);
								Lib_1.SaveAllotedBooksWithL();
								cout<<endl<<"Press any key to return to Member Portal...";
								_getch();
							}

							if(finalChoice == 2)
							{
								system("CLS");
								Lib_1.ReturnABook(ID);
								Lib_1.SaveAllotedBooksWithoutL();
								cout<<endl<<"Press any key to return to Member Portal...";
								_getch();
							}

							if(finalChoice == 3)
							{
								system("CLS");
								cout<<"Your Books: "<<endl;
								User* Current = Lib_1.ReturnUserByID(ID);
								Current -> DisplayAssignedBooks();
								cout<<endl<<"Press any key to return to Member Portal...";
								_getch();
							}
						
							if(finalChoice == 4)
							{
								system("CLS");
								cout<<"All Books: "<<endl;
								Lib_1.ShowBooks();
								cout<<endl<<"Press any key to return to Member Portal...";
								_getch();
							}

							if(finalChoice == 5)
							{
								system("CLS");
								cout<<"Your Details: "<<endl;
								Lib_1.ShowMember(ID);
								cout<<endl<<"Press any key to return to Member Portal...";
								_getch();
							}

							if(finalChoice == 6)
							{
								system("CLS");
								Lib_1.ChangePass(ID);
								cout<<endl<<"Press any key to return to Member Portal...";
								_getch();
							}
						}
					}
					else
					{
						cout<<"Invalid Username or Password"<<endl<<endl;
						cout<<"Press any key to return to previous menu...";
						_getch();
					}

				}

				if(inChoice == 2)
				{
					system("CLS");
					cout<<"Thank you for choosing us!!"<<endl;
					cout<<"Lets Sign you up :)"<<endl;
					Lib_1.AddMember();
					cout<<"Press any key to return to Member Menu..."<<endl;
					_getch();
				}
				Lib_1.SaveBooksToFile();
				Lib_1.SaveMembersToFile();
				Lib_1.LoadBooks();
				Lib_1.LoadMembers();
			}
		}
		else if( choice == 3 )
		{
			system("CLS");
			cout<<"\nThank You for choosing our Library!\n\nHAPPY READING!"<<endl;
			cout<<"------------------------------------------------------------"<<endl;
		}
	}
}

// Main 
void main()
{
	// Single Function with all running Functionality
	Run();
	system("pause");
}