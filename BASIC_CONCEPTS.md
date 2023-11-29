# Basic Concepts 
[source cppreference](https://en.cppreference.com/w/cpp/language/basic_concepts)

This section provides definitions for the specific terminology and the concepts used when describing
the C++ programming language.

A C++ program is a sequence of text files (typically header and source files) that contain **declarations**. They undergo **translation** to become an executable program, which is executed when the C++ implementation calls its **main function**.

Certain words in a C++ program have special meaning, and these are known as **keywords**. Others can be used as **identifiers**. Comments are ignored during translation. C++ program also contain **literals**, the values of characters inside them are determinded by **character sets and encodings**. Certain characters in the program have to be represented with **escape sequences**.

The entities of a C++ program are values, **objects**, **references**, **structured bindings** (since C++17), **functions**, **enumerators**, **types**, class members, **templates**, **templates specializations**, **parameter packs** (since C++11), and **namespaces**. Preprocessor **macros** are not C++ entities.

**Declarations** may introduce entities, associate them with **names** and define their properties. The declarations that define all properties required to use an entity are **definitions**. A program must contain only one definition of any non-inline function or variable that is **odr-used**.

Definitions of functions usually include sequences of **statements**, some of which include **expressions**, which specify the computations to be performed by the program.

Names encounteres in a program are associated with the declarations that introduced them using **neme lookup**. Each name is only valid within a part of the program called its **scope**. Some names have **linkage** which makes them refer to the same entities when they appear in different scopes or translation units.

Each object, reference, function, expression in C++ is associated with a **type**, which may be **fundamental**, compound, or **user-defined**, complete or **incomplete**, etc.

Declared objects and declared references that are not **non-static data members** are variables. 

## Declarations
Declarations are how names are introduced (or re-introduced) into the C++ program. Not all declarations actually declare anything, and each kind of entity is declared differently.

## Definitions
Definitions are declarations that are sufficient to use the entity identified by the name.

## Translation
Translation is the process of transforming text (C++ code) in something that the machine will understand (executable or libs). Translation has 9 phases that will be explained in another file.

## Main function
A program shall contain a global function named **main**, which is the designated start of the program in hosted environment.

## Keywords
Keywords (also know as reserved words) have special meaning to the compiler and are always written or typed in short(lower) cases. Keywords are words that the language uses for a special purpose, such as **void**, **int**, **public**, etc. It can't be used for a variable name or function name or any other identifiers.

## Identifiers
An identifier is an arbitrarily long sequence of digits, underscores, lowercase and uppercase Latin letters, and most Unicode Characters.

## Comments
Comments serve as a sort of in-code documentation. When inserted into a program, they are effectively ignored by the compiler; they are solely intended to be used as notes by the humans that read source code.

## Literals
Literals are the tokens of a C++ program that represent constant values embedded in the source code.

## Character sets and encodings
Character sets are the group of charactes that can be used to write a program and encoding is the process of switching from character to memory or vice versa.

## Escape sequences
Escape sequences are used to represent certain special characters within string literals and character literals.

## Classes
The basic purpose of a Class is to identify the common attributes and behaviours and group them as an entity that can be reused again and again for similar purposes.

## Objects
The Objects are such entities that are created based on these classes to follow that purpose.
All data members and member functions of the class can be accessed with the help of objects.

## References
Declares a named variable as a reference, that is, an alias to an already-existing object or function.

## Structured bindings (since C++17)
Binds the specified names to subobjects or elements of the initializer.

Like a reference, a structured biding is an alias to an existing object. Unlike a reference, a structured binding does not have to be of a reference type.

## Functions
Functions are C++ entities that associate a sequence of statements (a function body) with a name and a list of zero or more function parameters.

## Enumerators
An enumeration is a distinct type whose value is restricted to a range of values, which may include several explicitly named constants ("enumerators").

## Types
Objects, references, functions including function template specializations, and expressions have a property called type, which both restrict the operations that are permitted for those entities and provides semantic meaning to the otherwise generic sequences of bits.

## Class members
Components of a class, functions and attributes.

## Templates
A template is a C++ entity that defines one of the following:
- a family of classes (class template), which may be nested classes
- a family of functions (function template), which may be nested classes
- an alias to a family of types (alias template) - since C++11
- a family of variables (variable template) - since C++14
- a concept (constraints and concepts) - since C++20

## Template specializations
Allows customizing the template code for a given set of template arguments

## Parameter packs - Since C++11
A template parameter pack is a template parameter that accepts zero or more template arguments (non-type, type, or templates). A function parameter pack is a function parameter that accepts zero or more function arguments.

A template with at least one parameter pack is called a variadic template.

## Namespaces
Namespaces provide a method for preventing name conflicts in large projects.

Entities declared inside a namespace block are placed in a namespace scope, which prevents them from being mistaken for identically-named entities in other scopes.

## Preprocessor Macros
A macro is a fragment of code which has been given name. Whenever the name is used, it is replaced by the contents of the macro.

## One definition Rule
Only one definition of any variable, function, class type, enumeration type, concept (since C++20) or template is allowed in any one translation unit (some of these may have multiple declarations, but only one definition is allowed).

## Odr-used
- an object is odr-used if its value is read (unless it is a compile time constant) or written, its address is taken, or a reference is bound to it
- a reference is odr-used if it is used and its referent is not known at compile time
- a function is odr-used if a function call to it is made or its address is taken

If an object, a reference or a function is odr-used, its definition must exist somewhere in the program; a violation of that is ususally a link-time error.

## Statements
Statements are fragments of the C++ program that are executed in sequence. The body of any function is a sequence of statements.

## Expressions
An expression is a sequence of operators and their operands, that specifies a computation.

## Name
A name is the use of one of the following to refer to an entity
- an identifier
- and overloaded operator name in function notation (operator+, operator new)
- a user-defined conversion function name (operator bool)
- a user-defined literal operator name (operator ""_km) - Since C++11
- a template name followed by its argument list (MyTemplate<int>)

## Name lookup
Name lookup is the procedure by which a name, when encountered in a program, is associated with the declaration that introduced it.

## Scope
Each declaration that appears in a C++ program is only visible in some possibly discontiguous scopes. Within a scope, unqualified name lookup can be used to associate a name with its declaration.

## Linkage
Provides for linkage between program units written in different programming languages.

## Non-static data members
Any data member that is not declared as static. Non-static data members are declared in a member specification of a class.