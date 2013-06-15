/*
* Copyright 2013 the original author or authors.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*      http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/**********************************************************************
 * Author:      Owen Wu/wcw/yubing
 * Email:       yubing744@163.com
 * Created:     2013/03/31
 **********************************************************************/

#include <dragon/util/regex/Pattern.h>

Import dragon::lang;
Import dragon::util::regex;


#define OVECCOUNT 30    /* should be a multiple of 3 */

Pattern::Pattern(pcre32* re) {
    this->re = re; 
}

Pattern::~Pattern() {
    pcre32_free(this->re);
}

Pattern* Pattern::compile(String* regex) {
    const char *error;
    int erroffset;

    dg_char* pattern = (dg_char*)regex->toChars();

    pcre32* re = pcre32_compile(
        pattern,              /* the pattern */
        0,                    /* default options */
        &error,               /* for error message */
        &erroffset,           /* for error offset */
        NULL);                /* use default character tables */

    if (re != NULL) {
        return new Pattern(re);
    }

    return null;
}

Matcher* Pattern::matcher(String* input) {
    const dg_char* subject = input->toChars();
    dg_int subject_length = input->length();
 
    int ovector[OVECCOUNT];

    int rc = pcre32_exec(
      this->re,             /* the compiled pattern */
      NULL,                 /* no extra data - we didn't study the pattern */
      subject,              /* the subject string */
      subject_length,       /* the length of the subject */
      0,                    /* start at offset 0 in the subject */
      0,                    /* default options */
      ovector,              /* output vector for substring information */
      OVECCOUNT);           /* number of elements in the output vector */

    /* Matching failed: handle error cases */

    if (rc < 0) {
        switch(rc) {
            case PCRE_ERROR_NOMATCH: 
                printf("No match\n"); 
                break;
            /*
            Handle other special cases if you like
            */
            default: 
                printf("Matching error %d\n", rc); 
                break;
        }
        
        pcre32_free(this->re);     /* Release memory used for the compiled pattern */
        
        return new Matcher(subject, ovector, 0);
    } else {
        return new Matcher(subject, ovector, rc);
    }
}
