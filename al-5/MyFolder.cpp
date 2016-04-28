#include "MyFolder.h"
#include "MyFile.h"
#include "exceptions.h"


MyFolder::MyFolder(shared_ptr<MyFolder> parent, string name) : FileSystemElement(parent, name) {
	if (parent != shared_ptr<MyFolder>(nullptr)) {
		cout << "*this:\t" << typeid(*this).name() << endl;
		parent->add_child(dynamic_pointer_cast<FileSystemElement>(shared_from_this()));
	}
}


MyFolder::~MyFolder(void)
{
}


weak_ptr<MyFolder> MyFolder::get_parent_folder_ptr(void) const { return parent; }


void MyFolder::add_child(const shared_ptr<FileSystemElement> child) {
	cout << "child:\t" << typeid(*child).name() << endl;
	element.push_back(child);
	cout << "*element[]:\t" << typeid(*element.back()).name() << endl;

	return;
}


void MyFolder::list(void) const {
	vector<shared_ptr<FileSystemElement>>::const_iterator it;
	for (it = element.cbegin(); it != element.cend(); it++)
		cout << typeid(**it).name() << "\t"  << (*it)->get_name() << endl;
}


vector<weak_ptr<FileSystemElement>> MyFolder::find(string target_name) const {
	vector<weak_ptr<FileSystemElement>> result;
	for (auto el : element)
		if (el->get_name() == target_name)
			result.push_back(el);

	return result;
}