#ifndef _ELEMENTMANAGER_h
#define _ELEMENTMANAGER_h

class ElementManager
{
private:
	size_t count;
	Element* elements;

	void resize(size_t size);

public:
	ElementManager();

	void add(Element element);
	void react(Input input);
};

#endif

