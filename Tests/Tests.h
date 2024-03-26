/**
 * @file Tests.h
 * @author Santos F. Fregoso
 * @date 03/25/2024
 * @brief Tests header file
 * 
 * @note This software is part of the "Vast Take-Home Coding Excersise" issued on 03/19/2024
*/
#ifndef _TESTS_H_
#define _TESTS_H_

namespace Tests
{

    class Tests
    {

        /**
         * @note Testing incomplete but the desire would be the following
         * 
         * Use Google test as unit testing frame work would be ideal
         * 
         * Without Google test, I would use this `Test` class and add test functions
         * to test
         * 
         * - Truck thread receipt of done signal from 
         * - Statistics functions
         * - Creation of truck and 
         * - Out of range limit tests.
         * 
        */

        public:

        Tests();
        ~Tests();

        void runAllTests();

        private:
    
    };
    
}

#endif