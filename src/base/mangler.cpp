#include "mangler.h"

Mangler::Mangler() {}

Mangler::~Mangler() {}

Mangler::Interpreter::Interpreter() {}
Mangler::Interpreter::~Interpreter() {}

void* Mangler::Interpreter::getFileHeader()
{
    return nullptr;
}

void* Mangler::Interpreter::getProgramHeader()
{
    return nullptr;
}

void* Mangler::Interpreter::getSectionHeader()
{
    return nullptr;
}

void* Mangler::Interpreter::getSection()
{
    return nullptr;
}

void* Mangler::Interpreter::getSymbol()
{
    return nullptr;
}

void* Mangler::Interpreter::getString()
{
    return nullptr;
}

void* Mangler::Interpreter::getVariable()
{
    return nullptr;
}

void* Mangler::Interpreter::getHexa()
{
    return nullptr;
}

Mangler::Modifier::Modifier() {}

Mangler::Modifier::~Modifier() {}

bool Mangler::Modifier::alterFileHeader()
{
    return false;
}

bool Mangler::Modifier::alterSection()
{
    return false;
}

bool Mangler::Modifier::alterSymbol()
{
    return false;
}

bool Mangler::Modifier::alterString()
{
    return false;
}

bool Mangler::Modifier::alterVariable()
{
    return false;
}

bool Mangler::Modifier::alterFree()
{
    return false;
}
