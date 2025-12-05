#include "ObjParser.hpp"

void	ObjParser::NewObject(std::istringstream& ss)
{
	this->currentObject->activeGroups.clear();

	std::string	currentObjectStr;
	if (!(ss >> currentObjectStr))
		currentObjectStr = "default";
	this->currentObject = &this->objects[currentObjectStr];
	this->currentObject->activeGroups.emplace_back(&this->currentObject->groups[currentObjectStr]);
	if (ss >> std::ws; ss.peek() != EOF)
		ThrowError("Too many arguments in `o`, you can only create one object at a time", this->countLines);
}

void	ObjParser::SetGroups(std::istringstream& ss)
{
	this->currentObject->activeGroups.clear();

	std::string	currentGroup;
	while (ss >> currentGroup)
		this->currentObject->activeGroups.emplace_back(&this->currentObject->groups[currentGroup]);
	if (this->currentObject->activeGroups.size() == 0)
		this->currentObject->activeGroups.emplace_back(&this->currentObject->groups["default"]);
}

void	ObjParser::AddToGroups(std::string& prefix)
{
	std::variant<
		std::vector<Face>*,
		std::vector<Line>*,
		std::vector<Point>*
	> vec;

	if (prefix == "f")
		vec = &raw.faces;
	else if (prefix == "l")
		vec = &raw.lines;
	else if (prefix == "p")
		vec = &raw.points;
	else
		return;

	for (Group* group : this->currentObject->activeGroups) {
		std::visit([&group](auto* v){
			group->faceIndices.emplace_back(v->size());
		}, vec);
	}

	if (this->currentSmoothingGroup > 0)
	{
		SmoothingGroup&	smoothGroup = this->smoothingGroups[this->currentSmoothingGroup];
		std::visit([&smoothGroup](auto* v){
			smoothGroup.faceIndices.emplace_back(v->size());
		}, vec);
	}
}

// For curves -> store this->currentSmoothingGroup > 0 in a bool
void	ObjParser::SetSmoothingGroup(std::istringstream& ss)
{
	this->currentSmoothingGroup = -1;

	if (ss >> this->currentSmoothingGroup && this->currentSmoothingGroup == 0)
		this->currentSmoothingGroup = -1;
	else if (ss.fail())
	{
		std::string value;
		ss.clear();
		ss >> value;
		if (value == "on")
			this->currentSmoothingGroup = 1;
	}
}
