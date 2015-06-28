/**
 * @file   Debug.h
 * @author Thomas Pfeiffer
 * @date   Jun 28, 2015
 * @brief
 */

#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef DEBUG
#define ASSERT(x) if (!(x)) { while(!(x)) {} }
#else
#define ASSERT(x)
#endif

#endif /* _DEBUG_H_ */
