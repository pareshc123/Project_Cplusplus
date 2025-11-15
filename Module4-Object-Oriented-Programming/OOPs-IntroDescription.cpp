/*
    Introduction to Object Oriented Programming (OOP)
    -------------------------------------------------

    Object Oriented Programming is a programming paradigm in which
    software is designed using objects rather than algorithms.
    An object is an instance of a class. A class defines the
    structure and behavior of its objects.

    OOP helps in building software that is reusable, maintainable,
    scalable, and closer to real-world systems.

    The Object Model consists of four fundamental principles:
    1. Abstraction
    2. Encapsulation
    3. Inheritance
    4. Polymorphism

    1. Abstraction
    ----------------
    Abstraction means focusing on the essential characteristics of
    an object while ignoring unnecessary details. It reduces
    complexity by allowing programmers to represent real-world
    objects in a simplified form.

    Example:
        Representing a person only using a name, without including
        age, height, or other details. The important characteristics
        depend on the domain of the application.

    Abstraction in C++ is implemented using:
        - classes
        - structs
        - interfaces (via abstract classes)
        - enums
        - unions

    2. Encapsulation
    ------------------
    Encapsulation means hiding the internal implementation details
    of a class and exposing only the necessary functionality.
    This protects the internal state of an object and prevents
    unintended interference.

    In C++, encapsulation is achieved using:
        - private, protected, and public access specifiers

    Benefits:
        - Implementation can be changed without affecting the users
          of the class.
        - The class becomes easier to use and maintain.

    3. Inheritance
    ----------------
    Inheritance allows one class to acquire properties and behavior
    of another class. The class being inherited from is called the
    base class, and the class inheriting is the derived class.

    This relationship is also known as "is-a" or "generalization".
    Example:
        A Dog is an Animal.
        Dog can inherit behavior defined in Animal.

    Benefits:
        - Code reuse
        - Extensibility

    C++ supports several types of inheritance:
        - Single inheritance
        - Multiple inheritance
        - Multilevel inheritance
        - Hierarchical inheritance
        - Hybrid inheritance

    4. Polymorphism
    -----------------
    Polymorphism means "many forms". It allows objects of different
    types to be treated through a common interface, while each object
    can provide its own implementation of behaviors.

    Two types of polymorphism in C++:
        1. Compile-time polymorphism:
            Achieved using function overloading and templates.

        2. Runtime polymorphism:
            Achieved using virtual functions and inheritance.

    Example:
        Different objects (Car, Cycle, Person) can all have a
        function named Move, but each implements it differently.
        The correct version is chosen at runtime.

    Additional Concept: Composition
    --------------------------------
    Composition represents a "has-a" or "part-of" relationship
    between objects. It is another way to achieve reuse.

    Example:
        A Car has an Engine.
        An Engine object can be reused by the Car object.

    Summary
    --------
    Abstraction allows us to focus on essential details.
    Encapsulation hides implementation details.
    Inheritance allows code reuse through class relationships.
    Polymorphism allows different behaviors through a common interface.

    Together, these principles make OOP more reusable, maintainable,
    and easier to extend. C++ supports all of these principles and
    provides features like classes, objects, constructors, destructors,
    inheritance, and virtual functions to fully implement OOP.

*/

int main() {
    return 0;
}
