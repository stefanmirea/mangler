#ifndef MANGLER_H_
#define MANGLER_H_

class Mangler
{
public:
    Mangler();
    virtual ~Mangler();

private:
    class Interpreter
    {
    public:
        Interpreter();

        void *getFileHeader();
        void *getProgramHeader();
        void *getSectionHeader();
        void *getSection();
        void *getSymbol();
        void *getString();
        void *getVariable();
        void *getHexa();

        virtual ~Interpreter();
    };

    class Modifier
    {
    public:
        Modifier();

        bool alterFileHeader();
        bool alterSection();
        bool alterSymbol();
        bool alterString();
        bool alterVariable();
        bool alterFree();

        virtual ~Modifier();
    };

    Interpreter interpreter;
    Modifier modifier;
};

#endif
