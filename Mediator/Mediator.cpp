/*
 * Mediator
 * ========
 * Intent:
 * 1, Define an object that encapsulates how a set of objects interact. Mediator promotes loose coupling by keeping objects from referring to each other explicitly, and it lets you vary their interaction independently.
 * 2, Design an intermediary to decouple many peers.
 * 3, Promote the many-to-many relationships between interacting peers to "full object status".
 * 
 * Structure:
 * Colleagues (or peers) are not coupled to one another. 
 * Each talks to the Mediator, which in turn knows and conducts the orchestration of the others. 
 * The "many to many" mapping between colleagues that would otherwise exist, has been "promoted to full object status".
 *
 * */

#include<iostream>
#include<string.h>

class FileSelectionDialog;

class Widget
{
public:
	Widget(FileSelectionDialog* mediator, const char* name)
	{
		_mediator = mediator;
		strcpy(_name, name);
	}
	virtual ~Widget(){}
	virtual void changed();
	virtual void updateWidget() = 0;
	virtual void queryWidget() = 0;
protected:
	char _name[20];
private:
	FileSelectionDialog* _mediator;
};

class List: public Widget
{
public:
	List(FileSelectionDialog* dir, const char* name): Widget(dir, name){}
	void queryWidget()
	{
		std::cout << " " << _name << " list queried" << std::endl;
	}
	void updateWidget()
	{
		std::cout << " " << _name << " list updated" << std::endl;
	}
};

class Edit: public Widget
{
public:
	Edit(FileSelectionDialog* dir, const char* name) : Widget(dir, name){}
	void queryWidget()
	{
		std::cout << " " <<_name << " edit queried" << std::endl;
	}
	void updateWidget()
	{
		std::cout << " " << _name << " edit updated" << std::endl;
	}
private:
};

class FileSelectionDialog
{
public:
	enum Widgets
	{
		FilterEdit, DirList, FileList, SelectionEdit
	};
	FileSelectionDialog()
	{
		_components[FilterEdit] = new Edit(this, "filter");
		_components[DirList] = new List(this, "dir");
		_components[FileList] = new List(this, "file");
		_components[SelectionEdit] = new Edit(this, "selection");
	}
	virtual ~FileSelectionDialog();
	void handleEvent(int which)
	{
		_components[which]->changed();
	}
	virtual void widgetChanged(Widget *theChangedWidget)
	{
		if (theChangedWidget == _components[FilterEdit])
		{
			_components[FilterEdit]->queryWidget();
			_components[DirList]->updateWidget();
			_components[FileList]->updateWidget();
			_components[SelectionEdit]->updateWidget();
		}
		else if (theChangedWidget == _components[DirList])
		{
			_components[DirList]->queryWidget();
			_components[FileList]->updateWidget();
			_components[FilterEdit]->updateWidget();
			_components[SelectionEdit]->updateWidget();
		}
		else if (theChangedWidget == _components[FileList])
		{
			_components[FileList]->queryWidget();
			_components[SelectionEdit]->updateWidget();
		}
		else if (theChangedWidget == _components[SelectionEdit])
		{
			_components[SelectionEdit]->queryWidget();
			std::cout << "   file opened" << std::endl;
		}
	}
private:
	Widget* _components[4];
};

FileSelectionDialog:: ~FileSelectionDialog()
{
	for(int i=0; i<4; i++)
		delete _components[i];
}

void Widget::changed()
{
	_mediator->widgetChanged(this);
}

int main()
{
  FileSelectionDialog fileDialog;
  int i;

	std::cout << "Exit[0], Filter[1], Dir[2], File[3], Selection[4]: ";
	std::cin >> i;

  while (i)
  {
	    fileDialog.handleEvent(i - 1);
			std::cout << "Exit[0], Filter[1], Dir[2], File[3], Selection[4]: ";
			std::cin >> i;
	  }
}
