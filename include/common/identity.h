#ifndef IDENTITY_H_
#define IDENTITY_H_

/* This struct is often passed by value in the library, so it must
 * not contain any pointer */
typedef struct {
    uint16_t udid;
    uint16_t random;
} identity_t;

pull_error update_random(identity_t* identity);

#endif /* IDENTITY_H_ */
