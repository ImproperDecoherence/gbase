#include <sstream>

#include "gvector.hpp"
#include "testframework.hpp"

namespace gbase::test {

GTEST(GVectorTest) {
    GVector v1 = {'A', 'B', 'C', 'D'};
    GCHECK("Initalizer list 1", v1.size(), static_cast<size_t>(4));
    GCHECK("Initalizer list 2", v1[0], 'A');
    GCHECK("Initalizer list 3", v1[3], 'D');

    GVector v2{v1};
    GCHECK("Copy constructor 1", v2.size(), static_cast<size_t>(4));
    GCHECK("Copy constructor 2", v2[0], 'A');
    GCHECK("Copy constructor 3", v2[3], 'D');

    v2[1] = 'G';
    GCHECK("Operator[] asigment", v2[1], 'G');

    std::stringstream ss{""};
    v1.print(ss);
    const String expectedPrint{"[A, B, C, D]"};
    GCHECK("Print", ss.str(), expectedPrint);

    const GVector constUnsorted = {'B', 'A', 'D', 'C'};
    const GVector expectedSorted = {'A', 'B', 'C', 'D'};
    const GVector constSorted = constUnsorted.sort();
    GCHECK("Const sort", constSorted, expectedSorted);

    GVector unsorted = {'B', 'A', 'D', 'C'};
    unsorted.sort();
    GCHECK("Mutable sort", unsorted, expectedSorted);

    GVector toBeExtended{'B', 'A', 'D', 'C'};
    toBeExtended += 'D';
    GCHECK("Extend 1", toBeExtended, GVector{'B', 'A', 'D', 'C', 'D'});

    const GVector extendVector{'E', 'F'};
    toBeExtended += extendVector;
    GCHECK("Extend 2", toBeExtended, GVector{'B', 'A', 'D', 'C', 'D', 'E', 'F'});

    GVector rotateVector{'A', 'B', 'C', 'D'};
    rotateVector.rotate(+1);
    GCHECK("Rotate right", rotateVector, GVector {'D', 'A', 'B', 'C'});
    rotateVector.rotate(-2);
    GCHECK("Rotate left", rotateVector, GVector {'B', 'C', 'D', 'A'});
    rotateVector.rotate(8);
    GCHECK("Rotate wrap around", rotateVector, GVector {'B', 'C', 'D', 'A'});

    GVector rotateVectorInt{2, 5, 9};
    rotateVectorInt.rotate(+1);
    GCHECK("Rotate +1", rotateVectorInt, GVector {9, 2, 5});
    rotateVectorInt.rotate(+1);
    GCHECK("Rotate +2", rotateVectorInt, GVector {5, 9, 2});
    rotateVectorInt.rotate(+1);
    GCHECK("Rotate +3", rotateVectorInt, GVector {2, 5, 9});

    rotateVectorInt.rotate(+2);    
    GCHECK("Rotate +2", rotateVectorInt, GVector {5, 9, 2});
    rotateVectorInt.rotate(+1);
    GCHECK("Rotate +3", rotateVectorInt, GVector {2, 5, 9});

}

} // namespace gbase::test