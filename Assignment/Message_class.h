#include <string>
#include <set>
class Message;

class Folder {
	friend class Message;
public:
	void addMsg(Message* m) { messages.insert(m); }
	void remMsg(Message* m) { messages.erase(m); }
	std::set<Message*> getMessages() { return messages; }

private:
	std::set<Message*> messages;
};

class Message {
	friend class Folder;
public:
	explicit Message(const std::string& str = "") :
		contents(str) { }
	Message(const Message&);
	Message& operator=(const Message&);
	~Message();
	void save(Folder&);
	void remove(Folder&);
	void swap(Message&, Message&);
	std::string getContents();
private:
	std::string contents;
	std::set<Folder*> folders;
	void add_to_Folders(const Message&);
	void remove_from_Folders();
};

/*Functions of Message Class*/

void Message::save(Folder& f)
{
	folders.insert(&f);
	f.addMsg(this);
}

void Message::remove(Folder& f)
{
	folders.erase(&f);
	f.remMsg(this);
}

void Message::add_to_Folders(const Message& m)
{
	for (auto f : m.folders)
		f->addMsg(this);
}

void Message::remove_from_Folders()
{
	for (auto f : folders)
		f->remMsg(this);
	folders.clear();
}

Message::Message(const Message& m) :
	contents(m.contents), folders(m.folders)
{
	add_to_Folders(m);
}

Message::~Message()
{
	remove_from_Folders();
}

Message& Message::operator=(const Message& rhs)
{
	remove_from_Folders();
	contents = rhs.contents;
	folders = rhs.folders;
	add_to_Folders(rhs);
	return *this;
}

std::string Message::getContents()
{
	return contents;
}

void Message::swap(Message& lhs, Message& rhs)
{
	using std::swap;

	for (auto f : lhs.folders)
		f->remMsg(&lhs);
	for (auto f : rhs.folders)
		f->remMsg(&rhs);

	swap(lhs.folders, rhs.folders);
	swap(lhs.contents, rhs.contents);

	for (auto f : lhs.folders)
		f->addMsg(&lhs);
	for (auto f : lhs.folders)
		f->addMsg(&rhs);
}

