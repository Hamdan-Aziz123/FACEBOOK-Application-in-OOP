
#include<iostream>
#include<fstream>
using namespace std;

class Activity;
class Date;
class Post;
class Facebook;
class User;
class Page;
class Comment;
class Object;
class Memory;

class Helper
{
public:
	static int StringLenght(const char* str)
	{
		int length = 0;
		for (int i = 0; str[i] != '\0'; i++)
		{
			length++;
		}
		return length;
	}
	static void compressStr(char* str)
	{
		StringLenght(str);
		while (str[0] == ' ' || str[0] == '\t')
		{
			for (int i = 0; str[i] != '\0'; i++)
				str[i] = str[i + 1];
		}

	}
	static void StringCopy(char* dest, const char* src)
	{
		//Deep Copies src into dest.
		int i;
		for (i = 0; src[i] != '\0'; i++)
		{
			dest[i] = src[i];
		}
		dest[i] = '\0';
	}
	static char* GetStringFromBuffer(const char* str)
	{
		int n = StringLenght(str);
		n = n + 1;
		char* arr = new char[n];
		StringCopy(arr, str);
		return arr;
	}
	static bool comapreString(char* UserID, const char* userToSearch)
	{
		for (int i = 0; UserID[i] == userToSearch[i]; i++)
		{
			if (userToSearch[i + 1] == '\0')
			{
				return true;
			}
		}
		return false;
	}
};

class Object
{
private:
	char* ID;
public:
	Object(char* arr = 0)
	{
		if (arr == 0)
		{
			ID = arr;
		}
		else
		{
			ID = Helper::GetStringFromBuffer(arr);
		}
	}
	void setID(char* id)
	{
		ID = Helper::GetStringFromBuffer(id);
	}
	char* getID()
	{
		return ID;
	}

	virtual void printPost(bool f = 0) = 0;

	virtual void AddPost(Post*& p) = 0;

	virtual void viewTimeline() = 0;

	~Object()
	{
		if (ID != 0)
		{
			delete[] ID;
			ID = 0;
		}
	}
};
class Date
{
private:
	int Day;
	int Month;
	int Year;
public:
	static Date currentDate;
	Date(int d = 0, int m = 0, int y = 0)
	{
		Day = d;
		Month = m;
		Year = y;
	}
	static void setDate(int d, int m, int y)
	{
		currentDate.Day = d;
		currentDate.Month = m;
		currentDate.Year = y;
	}
	int year(Date rhs)
	{
		return Year - rhs.Year;
	}
	void datePrint()
	{
		cout << Day << " / " << Month << " / " << Year << "\n";
	}
	void loadDateFromFile(ifstream& fin)
	{
		fin >> Day;
		fin >> Month;
		fin >> Year;
	}
	bool compare(const Date& rhs)
	{
		if (Year == rhs.Year)
		{
			if (Month == rhs.Month)
			{
				if (Day + 1 == rhs.Day || Day == rhs.Day)
				{
					return true;
				}
			}
		}
		return false;
	}
	/*
		if (Year < rhs.Year)
		{
			return false;
		}
		else if (Year > rhs.Year)
		{
			return false;
		}
		else
		{
			if (Month < rhs.Month)
			{
				return false;
			}
			else if (Month > rhs.Month)
			{
				return false;
			}
			else
			{
				if (Day + 1 == rhs.Day || Day == rhs.Day)
				{
					return true;
				}
				else
				{
					return false;
				}

			}
		}
	}*/

};
Date Date::currentDate(0, 0, 0);
class Activity
{
private:
	int typeOfActivity;
	char* valueOfActivity;
public:

	Activity(int type = 0, char* value = 0)
	{
		typeOfActivity = type;
		if (value == 0)
		{
			valueOfActivity = value;
		}
		else
		{
			valueOfActivity = Helper::GetStringFromBuffer(value);
		}

	}
	void activityPrint()
	{
		if (typeOfActivity == 1)
		{
			cout << " Feeling ";
		}
		else if (typeOfActivity == 2)
		{
			cout << " Thinking About ";
		}
		else if (typeOfActivity == 3)
		{
			cout << " Making ";
		}
		else if (typeOfActivity == 4)
		{
			cout << " Celebrating ";
		}
		cout << "" << valueOfActivity;
	}
	void loadActivityFromFile(ifstream& fin)
	{
		fin >> typeOfActivity;
		char buffer[50];
		fin.getline(buffer, 50);
		Helper::compressStr(buffer);
		valueOfActivity = Helper::GetStringFromBuffer(buffer);
	}
	~Activity()
	{
		if (valueOfActivity != 0)
		{
			delete[] valueOfActivity;
			valueOfActivity = 0;
		}
	}
};
class Comment
{
private:
	char* commentID;
	char* commentText;
	Object* commentBy;
	static int totalComments;
public:
	static void setTotalComments(int x)
	{
		totalComments = x;
	}
	static int getTotalComments()
	{
		return totalComments;
	}
	void setValuesComment(char* id, const char* txt, Object* obj)
	{
		commentID = Helper::GetStringFromBuffer(id);
		commentText = Helper::GetStringFromBuffer(txt);
		commentBy = obj;
	}
	void commentPrint()
	{
		cout << "\t\t\t";
		commentBy->printPost();
		cout << " wrote: " << '\"' << commentText << '\"';
	}
	~Comment()
	{
		if (commentID != 0)
		{
			delete[] commentID;
			commentID = 0;
		}
		if (commentText != 0)
		{
			delete[] commentText;
			commentText = 0;
		}
		commentBy = 0;
	}
};
int Comment::totalComments = 0;

class Post
{
private:
	char* postID;
	int PostType;
	char* postText;
	Date sharedDate;
	Activity* activity;
	Object* sharedBy;
	Object** likedBy;
	Comment** comments;
	int noOfComments;
	int noOflikes;
	static int totalPosts;
public:
	Post()
	{
		postID = 0;
		PostType = 0;
		postText = 0;
		activity = 0;
		sharedBy = 0;
		likedBy = 0;
		comments = 0;
		noOfComments = 0;
		noOflikes = 0;
	}
	Date GetDateShared()
	{
		return sharedDate;
	}
	static void setTotalPosts(int x)
	{
		totalPosts = x;
	}
	static int getTotalPosts()
	{
		return totalPosts;
	}
	void setPostID(char* arr)
	{
		postID = Helper::GetStringFromBuffer(arr);
	}
	void setPostText(char* arr)
	{
		postText = Helper::GetStringFromBuffer(arr);
	}
	void setSharedDate(Date d)
	{
		sharedDate = d;
	}
	char* getPostText()
	{
		return postText;
	}
	char* getPostID()
	{
		return postID;
	}
	void setSharedByPost(Object*& obj)
	{
		sharedBy = obj;
	}
	void AddCommentToPost(Comment*& comnt)
	{
		if (noOfComments == 0)
		{
			comments = new Comment * [10];
		}
		comments[noOfComments] = comnt;
		noOfComments++;
	}
	void setLikedbyPost(Object*& obj)
	{
		if (noOflikes == 0)
		{
			likedBy = new Object * [10];
		}
		likedBy[noOflikes] = obj;
		noOflikes++;
	}
	void viewPostLikedBy()
	{
		cout << "Post Liked By: \n\n";
		for (int i = 0; i < noOflikes; i++)
		{
			likedBy[i]->printPost(true);
			cout << endl;
		}
	}
	void ReadPostsFromFIle(ifstream& file)
	{
		file >> PostType;
		char buffer[100];
		file >> buffer;
		postID = Helper::GetStringFromBuffer(buffer);
		sharedDate.loadDateFromFile(file);
		file.ignore();
		file.getline(buffer, 100);
		Helper::compressStr(buffer);
		postText = Helper::GetStringFromBuffer(buffer);
		if (PostType == 2)
		{
			activity = new Activity;
			activity->loadActivityFromFile(file);
		}
	}
	void Print(bool f = 0)
	{
		cout << "---";
		sharedBy->printPost();

		if (PostType == 2)
		{
			cout << " is";
			activity->activityPrint();
			cout << "   ";
			sharedDate.datePrint();
			cout << '\"' << postText << '\"' << "\n";

		}
		if (PostType == 1)
		{
			cout << " shared ";
			cout << '\"' << postText << '\"' << "\n";
			sharedDate.datePrint();
		}


		cout << endl;
		if (!f)
		{
			for (int i = 0; i < noOfComments; i++)
			{
				comments[i]->commentPrint();
				cout << endl;
			}
		}
		cout << "\n\n";
	}
	~Post()
	{
		if (postID != 0)
		{
			delete[] postID;
			postID = 0;
		}
		if (postText != 0)
		{
			delete[] postText;
			postText = 0;
		}

		for (int i = 0; i < 10; i++)
		{
			if (noOfComments-- > 0)
			{
				delete comments[i];
				comments[i] = 0;
			}
			if (noOflikes-- > 0)
				likedBy[i] = 0;
		}

		delete[] comments;
		delete[] likedBy;
		comments = 0;
		likedBy = 0;
		sharedBy = 0;
		if (activity != 0)
		{
			delete activity;
			activity = 0;
		}
	}
};
int Post::totalPosts = 0;

class Page :public Object
{
private:

	char* titlePage;
	static int totalNumOfPages;
	Post** timeline;
	int noOfPost;
public:
	Page(char* ttl = 0)
	{
		titlePage = ttl;
		timeline = 0;
		noOfPost = 0;
	}
	void setID(char* id)
	{
		Object::setID(id);
	}
	char* getID()
	{
		return Object::getID();
	}
	char* getTitle()
	{
		return titlePage;
	}
	static int getTotalPages()
	{
		return totalNumOfPages;
	}
	static void SetTotalPages(int x)
	{
		totalNumOfPages = x;
	}
	void AddPost(Post*& p)
	{
		if (noOfPost == 0)
			timeline = new Post * [10];
		timeline[noOfPost++] = p;
	}
	void viewTimeline()
	{
		cout << titlePage << "\n\n";
		for (int i = 0; i < noOfPost; i++)
		{
			timeline[i]->Print();
			cout << endl;
		}
	}
	void viewTimelineAccDate(Date& rhs)
	{
		for (int i = 0; i < noOfPost; i++)
		{
			if (timeline[i]->GetDateShared().compare(rhs))
			{
				timeline[i]->Print();
			}
			cout << endl;
		}
	}
	void ReadPagesFromFIle(ifstream& fin)
	{
		char temp[50];
		fin >> temp;
		setID(temp);
		fin.getline(temp, 50);
		Helper::compressStr(temp);
		titlePage = Helper::GetStringFromBuffer(temp);
	}
	void printPost(bool f = 0)
	{
		if (f)
		{
			cout << getID() << " - ";
		}
		cout << titlePage;
	}
	~Page()
	{

		if (titlePage != 0)
		{
			delete[] titlePage;
			titlePage = 0;
		}
		if (noOfPost > 0)
		{
			for (int i = 0; i < 10; i++)
			{
				if (noOfPost-- > 0)
				{
					delete timeline[i];
					timeline[i] = 0;
				}
			}
		}
		delete[] timeline;
		timeline = 0;
	}

};

int Page::totalNumOfPages = 0;
class Memory :public Post
{
private:
	Post* original;
public:
	Memory()
	{
		original = 0;
	}
	void set(Post*& p, const char* a, Object* obj)
	{
		original = p;
		setPostText((char*)a);
		setSharedByPost(obj);
		setSharedDate(Date::currentDate);

	}
	void print()
	{
		GetDateShared().datePrint();
		cout << '\"' << getPostText() << '\"' << "\n\n";
		cout << "(" << Date::currentDate.year(original->GetDateShared()) << " years ago)\n";
		original->Print(true);
	}
	~Memory()
	{
		original = 0;
	}
};

class User :public Object
{
private:
	char* firstName;
	char* lastName;
	Page** likedPages;
	int likePagesCounter;
	User** friendList;
	int friendsListCounter;
	Memory* Mmry;
	Post** timeline;
	int noOfPostsUserPosted;
	static int totalNumOfUsers;
public:
	User()
	{
		firstName = 0;
		lastName = 0;
		likedPages = 0;
		friendList = 0;
		likePagesCounter = 0;
		friendsListCounter = 0;
		timeline = 0;
		noOfPostsUserPosted = 0;
		Mmry = 0;
	}
	static int getTotalUsers()
	{
		return totalNumOfUsers;
	}
	static void setTotalUsers(int x)
	{
		totalNumOfUsers = x;
	}
	char* getID()
	{
		return Object::getID();
	}
	void setID(char* ch)
	{
		Object::setID(ch);
	}
	char* getFirstName()
	{
		return firstName;
	}
	char* getLastName()
	{
		return lastName;
	}
	void userlikePages(Page*& pg)
	{
		if (likePagesCounter == 0)
		{
			likedPages = new Page * [10];
		}
		likedPages[likePagesCounter] = pg;
		likePagesCounter++;
	}
	void userAddFriends(User*& usr)
	{
		if (friendsListCounter == 0)
		{
			friendList = new User * [10];
		}
		friendList[friendsListCounter] = usr;
		friendsListCounter++;
	}
	void AddPost(Post*& pst)
	{
		if (noOfPostsUserPosted == 0)
		{
			timeline = new Post * [10];
		}
		timeline[noOfPostsUserPosted] = pst;
		noOfPostsUserPosted++;
	}
	void viewFriendList()
	{
		cout << firstName << " " << lastName << " - Friend List \n";
		for (int i = 0; i < friendsListCounter; i++)
		{
			friendList[i]->printPost(true);
			cout << "\n";
		}
	}
	void viewLikedPages()
	{
		cout << firstName << " " << lastName << " - Liked Pages \n";
		for (int i = 0; i < likePagesCounter; i++)
		{
			likedPages[i]->printPost(true);
			cout << "\n";
		}
	}
	void phase1()
	{
		cout << "Command:\t" << "Set current user " << getID() << "\n";
		cout << firstName << " " << lastName << " successfully set as current user \n\n";
		cout << "Command: \t" << "View Friend List \n";
		cout << "\n ---------------------------------------------------------- \n";
		viewFriendList();
		cout << "\n ---------------------------------------------------------- \n";
		cout << "\nCommand: \t" << "View Liked Pages \n";
		cout << "\n ---------------------------------------------------------- \n";
		viewLikedPages();
		cout << "\n ---------------------------------------------------------- \n\n";

	}
	void HomeView()
	{
		cout << "\nCommand:\t" << "View Home \n";
		cout << "---------------------------------------------------------- \n";
		cout << firstName << " " << lastName << "- Home Page \n\n";
		Date::currentDate.setDate(15, 11, 2017);

		for (int i = 0; i < friendsListCounter; i++)
		{
			friendList[i]->viewTimelineAccDate(Date::currentDate);
		}
		for (int i = 0; i < likePagesCounter; i++)
		{
			likedPages[i]->viewTimelineAccDate(Date::currentDate);
		}
		cout << "\n ---------------------------------------------------------- \n\n";
	}
	void viewTimeline()
	{
		cout << "\n---------------------------------------------------------- \n";
		cout << "Command:\t" << "View Timeline\n";
		cout << "---------------------------------------------------------- \n";
		cout << firstName << " " << lastName << "-View Timeline\n\n\n";
		if (Mmry != nullptr)
		{
			cout << "~~~~" << firstName << ' ' << lastName << " Shared Memory~~~~";

			Mmry->print();
			cout << endl;
		}

		for (int i = 0; i < noOfPostsUserPosted; i++)
		{
			timeline[i]->Print();
			cout << endl;
		}
		cout << "\n ---------------------------------------------------------- \n\n";
	}
	void viewTimelineAccDate(Date& rhs)
	{

		/*if (Mmry != nullptr)
		{
			cout << "~~~~" << firstName << ' ' << lastName << " Shared Memory~~~~";
			Mmry->print();
			cout << endl;
		}*/

		for (int i = 0; i < noOfPostsUserPosted; i++)
		{

			if (timeline[i]->GetDateShared().compare(rhs))
			{
				timeline[i]->Print();
			}
			cout << endl;
		}
	}
	void likePost(Post*& p)
	{
		Object* obj = this;
		p->setLikedbyPost(obj);
	}
	void PostComment(Post* pst, const char* txt)
	{
		cout << "\n\n ---------------------------------------------------------- \n";
		cout << "Command:\t" << "Post Comment (" << pst->getPostID() << " , " << txt << ")\n";
		cout << "Command:\t" << "View Post (" << pst->getPostID() << ")\n\n\n";
		char ch[20] = "\0";
		Comment* c = new Comment;
		c->setValuesComment(ch, txt, this);

		pst->AddCommentToPost(c);
		pst->Print();
		cout << "\n ---------------------------------------------------------- \n\n";
	}
	void SeeYourMemory()
	{
		cout << "\n ---------------------------------------------------------- \n ";
		cout << "Command   :    See Your Memories\n\n";
		bool f1 = false;
		for (int i = 0; i < noOfPostsUserPosted; i++)
		{
			if (Date::currentDate.year(timeline[i]->GetDateShared()) >= 1)
			{
				f1 = true;
				cout << "On this Day\n";
				cout << "(" << Date::currentDate.year(timeline[i]->GetDateShared()) << " years ago)\n";
				timeline[i]->Print();
			}
		}
		if (f1 == false)
		{
			cout << "no memoryy....!!\n\n\n";
		}
		cout << "\n ---------------------------------------------------------- \n\n";
	}
	void shareMemory(const char* ch, const char* arr)
	{
		cout << "\n\n ---------------------------------------------------------- \n ";
		cout << "\nCommand: \t" << "Share Memories (" << ch << " , " << arr << ") \n";
		char* ID = 0;

		
		bool f1 = false;
		for (int i = 0; i < noOfPostsUserPosted; i++)
		{
			ID = timeline[i]->getPostID();
			if (Helper::comapreString(ID, ch) )
			{
				Mmry = new Memory;
				f1 = true;
				Mmry->set(timeline[i], arr, this);
				break;
			}
		}
		if (f1 == false)
		{
			Mmry = 0;
			cout << "\nmemory not found\n\n\n";
		}

		cout << "\n ---------------------------------------------------------- \n\n";
	}
	void ReadDataFromFile(ifstream& file)
	{
		char temp[50];
		file >> temp;
		setID(temp);
		file >> temp;
		firstName = Helper::GetStringFromBuffer(temp);
		file >> temp;
		lastName = Helper::GetStringFromBuffer(temp);
	}
	void printPost(bool f = 0)
	{
		if (f)
		{
			cout << getID() << " - ";
		}
		cout << firstName << " " << lastName;
	}
	~User()
	{

		if (firstName != 0)
		{
			delete[] firstName;
			firstName = 0;
		}
		if (lastName != 0)
		{
			delete[] lastName;
			lastName = 0;
		}
		for (int i = 0; i < 10; i++)
		{
			if (likePagesCounter > 0)
			{
				likedPages[i] = 0;
			}
			if (friendsListCounter > 0)
			{
				friendList[i] = 0;
			}
			if (noOfPostsUserPosted-- > 0)
			{
				delete timeline[i];
				timeline[i] = 0;
			}
		}
		delete[] likedPages;
		delete[] friendList;
		delete[] timeline;
		delete Mmry;
		likedPages = 0;
		friendList = 0;
		Mmry = 0;
		timeline = 0;
	}
};
int User::totalNumOfUsers = 0;

class Facebook
{
private:
	Page** pages;
	User** users;
	Post** posts;
	Comment** comments;
public:
	Facebook();
	void loadData();
	void loadPagesFromFile(const char*);
	void loadUsersFromFile(const char*);
	void loadCommentsFromFile(const char*);
	void loadPostsFromFile(const char*);
	User* searchUserByID(const char*);
	Page* searchPageByID(const char*);
	Post* searchPostByID(const char*);
	Object* getObjById(const char*);
	void viewLikedList(const char*);
	void viewPage(const char*);
	//void print();
	void run();
	~Facebook();
};
Facebook::Facebook()
{
	pages = 0;
	users = 0;
	posts = 0;
	comments = 0;
}
void Facebook::loadData()
{
	loadPagesFromFile("Pages.txt");
	loadUsersFromFile("Users.txt");
	loadPostsFromFile("Posts.txt");
	loadCommentsFromFile("Comments.txt");
}
void Facebook::loadCommentsFromFile(const char* file)
{
	ifstream fin;
	fin.open(file);
	if (fin.is_open())
	{
		int total = 0;
		fin >> total;
		Comment::setTotalComments(total);
		comments = new Comment * [total];
		char id[10];
		char text[100];

		for (int i = 0; i < total; i++)
		{
			comments[i] = new Comment;
			fin >> id;
			fin >> text;
			Post* pot = searchPostByID(text);
			fin >> text;
			Object* obj = getObjById(text);
			fin.getline(text, 100);
			Helper::compressStr(text);
			comments[i]->setValuesComment(id, text, obj);
			pot->AddCommentToPost(comments[i]);
			//comments = 0;

		}
	}
}
void Facebook::loadPostsFromFile(const char* file)
{
	ifstream fin;
	fin.open(file);
	char buffer[40];
	if (fin.is_open())
	{
		int total = 0;
		fin >> total;
		Post::setTotalPosts(total);
		posts = new Post * [total];
		for (int i = 0; i < total; i++)
		{
			posts[i] = new Post;
			posts[i]->ReadPostsFromFIle(fin);
			fin >> buffer;
			Object* obj = getObjById(buffer);
			posts[i]->setSharedByPost(obj);
			obj->AddPost(posts[i]);
			fin >> buffer;
			while (buffer[0] != '-')
			{
				Object* ob = getObjById(buffer);
				posts[i]->setLikedbyPost(ob);
				fin >> buffer;
			}
		}
	}
}
void Facebook::loadPagesFromFile(const char* file)
{
	ifstream fin;
	fin.open(file);
	if (fin.is_open())
	{
		int total = 0;
		fin >> total;
		Page::SetTotalPages(total);
		pages = new Page* [total];

		for (int i = 0; i < total; i++)
		{
			pages[i] = new Page;
			pages[i]->ReadPagesFromFIle(fin);
		}
	}
}
void Facebook::loadUsersFromFile(const char* file)
{
	ifstream fin;
	fin.open(file);
	if (fin.is_open())
	{
		int total = 0;
		fin >> total;
		char buffer[50];
		char*** userFriend = new char** [total];
		User::setTotalUsers(total);
		users = new User * [total];
		for (int i = 0; i < total; i++)
		{
			users[i] = new User;
			users[i]->ReadDataFromFile(fin);
			userFriend[i] = new char* [10];
			int j = 0;
			fin >> buffer;
			while (buffer[0] != '-')
			{
				userFriend[i][j++] = Helper::GetStringFromBuffer(buffer);
				fin >> buffer;
			}
			userFriend[i][j] = 0;

			fin >> buffer;
			while (buffer[0] != '-')
			{
				Page* pg = searchPageByID(buffer);
				users[i]->userlikePages(pg);
				fin >> buffer;
				pg = nullptr;
			}
		}
		for (int i = 0; i < total; i++)
		{
			for (int j = 0; userFriend[i][j] != 0; j++)
			{
				User* usr = searchUserByID(userFriend[i][j]);
				users[i]->userAddFriends(usr);
				usr = nullptr;
			}
		}
		for (int i = 0;i < total;i++)
		{
			for (int j = 0;userFriend[i][j] != 0;j++)
			{
				delete[] userFriend[i][j];
			}
			delete[] userFriend[i];
		}
		delete[] userFriend;

	}

}


User* Facebook::searchUserByID(const char* userToSearch)
{
	char* UserID = 0;
	for (int i = 0;i < users[i]->getTotalUsers(); i++)
	{
		UserID = users[i]->getID();
		if (Helper::comapreString(UserID, userToSearch) == true)
		{
			return users[i];
		}
	}
	return 0;
}
Page* Facebook::searchPageByID(const char* userToSearch)
{
	char* UserID = 0;
	for (int i = 0; i < pages[i]->getTotalPages(); i++)
	{
		UserID = pages[i]->getID();
		if (Helper::comapreString(UserID, userToSearch) == true)
		{
			return pages[i];
		}
	}
	return 0;
}
Post* Facebook::searchPostByID(const char* arr)
{
	char* ID = 0;
	for (int i = 0; i < Post::getTotalPosts(); i++)
	{
		ID = posts[i]->getPostID();
		if (Helper::comapreString(ID, arr) == true)
		{
			return posts[i];
		}
	}
	return 0;
}
Object* Facebook::getObjById(const char* a)
{
	User* usr = searchUserByID(a);
	if (usr != 0)
	{
		return usr;
	}
	Page* pg = searchPageByID(a);
	if (pg != 0)
	{
		return pg;
	}
	return 0;
}
void Facebook::viewLikedList(const char* arr)
{
	cout << "\n ---------------------------------------------------------- \n ";
	cout << "Commend   :    ViewLikedList(" << arr << ")\n\n";
	Post* p = searchPostByID(arr);
	p->viewPostLikedBy();
	cout << "\n ---------------------------------------------------------- \n\n";
}
void Facebook::viewPage(const char* ch)
{
	cout << "\n ---------------------------------------------------------- \n ";
	cout << "Commend   :    ViewPage(" << ch << ")\n\n";
	Page* p = searchPageByID(ch);
	p->viewTimeline();
	cout << "\n ---------------------------------------------------------- \n\n";
}
//void Facebook::print()
//{
//	for (int i = 0; i < Post::getTotalPosts(); i++)
//	{
//		posts[i]->Print();
//		cout << endl;
//	}
//}
void Facebook::run()
{

	User* user = searchUserByID("u7");
	if (user)
	{
		user->phase1();
		user->HomeView();
		user->viewTimeline();

		Post* p = searchPostByID("post5");
		if (p)
		{
			viewLikedList("post5");
			user->likePost(p);
			viewLikedList("post5");
		}
		else
		{
			cout << "post not found to show liked list\n\n\n";
		}

		Post* pst = searchPostByID("post4");
		if (pst)
		{
			user->PostComment(pst, "Good Luck for your Result");
		}
		else
		{
			cout << "post not found to comment on\n\n\n";
		}
		Post* pst2 = searchPostByID("post8");
		if (pst2)
		{
			user->PostComment(pst2, "Thanks for the wishes");
		}
		else
		{
			cout << "post not found to comment on\n\n\n";
		}

		user->SeeYourMemory();

		user->shareMemory("post10", "Never thought I will be specialist in this field...");
		Date::currentDate.setDate(15, 11, 2017);
		user->viewTimeline();

		viewPage("p1");
	}
	else
	{
		cout << "user not find\n\n\n\n\n";
	}
	
	User* usr = searchUserByID("u11");
	if (usr)
	{
		usr->phase1();
		usr->HomeView();
		usr->viewTimeline();
	}
	else
	{
		cout << "user not find\n\n\n\n\n";
	}
}
Facebook::~Facebook()
{
	for (int i = 0; i < Page::getTotalPages(); i++)
	{
		delete pages[i];
	}
	delete[] pages;
	pages = 0;
	Page::SetTotalPages(0);
	for (int i = 0; i < User::getTotalUsers(); i++)
	{
		delete users[i];
	}
	delete[] users;
	users = 0;
	User::setTotalUsers(0);

	delete[] posts;
	posts = 0;
	Post::setTotalPosts(0);

	delete[] comments;
	comments = 0;
	Comment::setTotalComments(0);
}
int main()
{
	Facebook fb;
	fb.loadData();
	//fb.print();
	fb.run();

	system("pause");
	return 0;
}