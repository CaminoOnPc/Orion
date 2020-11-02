/*
	File: IFileSystem.cpp

	Copyright (C) 2019-2020 Bionic Interactive. All rights reserved
*/

#include "IFileSystem.h"

//-----------------------------------------------------------------------------
// Activates IFileSystem initalization process
//-----------------------------------------------------------------------------
void IFileSystem::Start(IInterfaces* interfaces)
{
	m_Interface = interfaces;

	//! Change to recursive_directory_iterator if you want it to search in sub-directories too
	std::string objectsPath(Utils::get_current_directory() + "\\data\\game\\objects\\");
	std::string ext(".xml");
	for (auto& objectPath : std::filesystem::directory_iterator(objectsPath))
	{
		if (objectPath.path().extension() == ext)
		{
			std::ifstream objectsFile(objectsPath + objectPath.path().filename().string());
			std::vector<char> objectsBuffer((std::istreambuf_iterator<char>(objectsFile)), std::istreambuf_iterator<char>());
			objectsBuffer.push_back('\0');

			rapidxml::xml_document<> objectsDocument;
			objectsDocument.parse<0>(&objectsBuffer[0]);

			rapidxml::xml_node<>* objectsRoot;
			objectsRoot = objectsDocument.first_node("objects");

			for (rapidxml::xml_node<>* object_node = objectsRoot->first_node("object"); object_node; object_node = object_node->next_sibling())
			{
				HObject* object = new HObject;

				object->m_ModelName = object_node->first_attribute("name")->value();

				for (rapidxml::xml_node<>* model_node = object_node->first_node("model"); model_node; model_node = model_node->next_sibling("model"))
				{
					object->m_ModelPath = "data/game/";
					object->m_ModelPath.append(model_node->value());
				}

				m_Objects.push_back(object);
			}
		}
	}
}

//-----------------------------------------------------------------------------
// Activates IFileSystem shutdown process
//-----------------------------------------------------------------------------
void IFileSystem::Stop()
{
	m_Interface = nullptr;
}

//-----------------------------------------------------------------------------
// Processing a single frame of IFileSystem
//-----------------------------------------------------------------------------
void IFileSystem::Run()
{
	return;
}