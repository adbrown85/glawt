#
# functions.mak
#     Some helper functions for makefiles.
# 
# Author
#     Andrew Brown <adb1413@rit.edu>
#
include $(GANDER)/gmsl


# ----------------------------------------------------------------------------
# Function:  index
# Arguments: 1: Number to start at
#            2: Word to search for
#            3: List of words
# Returns:   Index of the word to search for
# ----------------------------------------------------------------------------
index = ${if $3,\
              ${if ${call seq,$2,${call first,$3}},\
                    $1,\
                    ${call index,${call inc,$1},$2,${call rest,$3}}\
               }\
         }

# ----------------------------------------------------------------------------
# Function:  before
# Arguments: 1: Word to search for
#            2: List of words
# Returns:   All the words before the word to search for
# ----------------------------------------------------------------------------
before = ${wordlist 1,${call index,0,$1,$2},$2}
