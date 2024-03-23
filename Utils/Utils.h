#ifndef _UTILS_H_
#define _UTILS_H_

namespace Utils
{
    /**
     * @brief Starting point for generation of random number
    */
    void randStart(void);

    /**
     * @brief Generate random floating number between
     * 0 and (1/256)
    */
    float randFlt(void);

    int64_t compTimespecDiff(struct timespec left, struct timespec right);
}

#endif