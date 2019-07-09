# str
str(object='') -> string

Return a nice string representation of the object.
If the argument is a string, the return value is the same object.
- - -

## str.capitalize
S.capitalize() -> string

Return a copy of the string S with only its first character
capitalized.
- - -

## str.center
S.center(width[, fillchar]) -> string

Return S centered in a string of length width. Padding is
done using the specified fill character (default is a space)
- - -

## str.count
S.count(sub[, start[, end]]) -> int

Return the number of non-overlapping occurrences of substring sub in
string S[start:end].  Optional arguments start and end are interpreted
as in slice notation.
- - -

## str.decode
S.decode([encoding[,errors]]) -> object

Decodes S using the codec registered for encoding. encoding defaults
to the default encoding. errors may be given to set a different error
handling scheme. Default is 'strict' meaning that encoding errors raise
a UnicodeDecodeError. Other possible values are 'ignore' and 'replace'
as well as any other name registered with codecs.register_error that is
able to handle UnicodeDecodeErrors.
- - -

## str.encode
S.encode([encoding[,errors]]) -> object

Encodes S using the codec registered for encoding. encoding defaults
to the default encoding. errors may be given to set a different error
handling scheme. Default is 'strict' meaning that encoding errors raise
a UnicodeEncodeError. Other possible values are 'ignore', 'replace' and
'xmlcharrefreplace' as well as any other name registered with
codecs.register_error that is able to handle UnicodeEncodeErrors.
- - -

## str.endswith
S.endswith(suffix[, start[, end]]) -> bool

Return True if S ends with the specified suffix, False otherwise.
With optional start, test S beginning at that position.
With optional end, stop comparing S at that position.
suffix can also be a tuple of strings to try.
- - -

## str.expandtabs
S.expandtabs([tabsize]) -> string

Return a copy of S where all tab characters are expanded using spaces.
If tabsize is not given, a tab size of 8 characters is assumed.
- - -

## str.find
S.find(sub [,start [,end]]) -> int

Return the lowest index in S where substring sub is found,
such that sub is contained within S[start:end].  Optional
arguments start and end are interpreted as in slice notation.

Return -1 on failure.
- - -

## str.format
S.format(*args, **kwargs) -> string

Return a formatted version of S, using substitutions from args and kwargs.
The substitutions are identified by braces ('{' and '}').
- - -

## str.index
S.index(sub [,start [,end]]) -> int

Like S.find() but raise ValueError when the substring is not found.
- - -

## str.isalnum
S.isalnum() -> bool

Return True if all characters in S are alphanumeric
and there is at least one character in S, False otherwise.
- - -

## str.isalpha
S.isalpha() -> bool

Return True if all characters in S are alphabetic
and there is at least one character in S, False otherwise.
- - -

## str.isdigit
S.isdigit() -> bool

Return True if all characters in S are digits
and there is at least one character in S, False otherwise.
- - -

## str.islower
S.islower() -> bool

Return True if all cased characters in S are lowercase and there is
at least one cased character in S, False otherwise.
- - -

## str.isspace
S.isspace() -> bool

Return True if all characters in S are whitespace
and there is at least one character in S, False otherwise.
- - -

## str.istitle
S.istitle() -> bool

Return True if S is a titlecased string and there is at least one
character in S, i.e. uppercase characters may only follow uncased
characters and lowercase characters only cased ones. Return False
otherwise.
- - -

## str.isupper
S.isupper() -> bool

Return True if all cased characters in S are uppercase and there is
at least one cased character in S, False otherwise.
- - -

## str.join
S.join(iterable) -> string

Return a string which is the concatenation of the strings in the
iterable.  The separator between elements is S.
- - -

## str.ljust
S.ljust(width[, fillchar]) -> string

Return S left-justified in a string of length width. Padding is
done using the specified fill character (default is a space).
- - -

## str.lower
S.lower() -> string

Return a copy of the string S converted to lowercase.
- - -

## str.lstrip
S.lstrip([chars]) -> string or unicode

Return a copy of the string S with leading whitespace removed.
If chars is given and not None, remove characters in chars instead.
If chars is unicode, S will be converted to unicode before stripping
- - -

## str.partition
S.partition(sep) -> (head, sep, tail)

Search for the separator sep in S, and return the part before it,
the separator itself, and the part after it.  If the separator is not
found, return S and two empty strings.
- - -

## str.replace
S.replace(old, new[, count]) -> string

Return a copy of string S with all occurrences of substring
old replaced by new.  If the optional argument count is
given, only the first count occurrences are replaced.
- - -

## str.rfind
S.rfind(sub [,start [,end]]) -> int

Return the highest index in S where substring sub is found,
such that sub is contained within S[start:end].  Optional
arguments start and end are interpreted as in slice notation.

Return -1 on failure.
- - -

## str.rindex
S.rindex(sub [,start [,end]]) -> int

Like S.rfind() but raise ValueError when the substring is not found.
- - -

## str.rjust
S.rjust(width[, fillchar]) -> string

Return S right-justified in a string of length width. Padding is
done using the specified fill character (default is a space)
- - -

## str.rpartition
S.rpartition(sep) -> (head, sep, tail)

Search for the separator sep in S, starting at the end of S, and return
the part before it, the separator itself, and the part after it.  If the
separator is not found, return two empty strings and S.
- - -

## str.rsplit
S.rsplit([sep [,maxsplit]]) -> list of strings

Return a list of the words in the string S, using sep as the
delimiter string, starting at the end of the string and working
to the front.  If maxsplit is given, at most maxsplit splits are
done. If sep is not specified or is None, any whitespace string
is a separator.
- - -

## str.rstrip
S.rstrip([chars]) -> string or unicode

Return a copy of the string S with trailing whitespace removed.
If chars is given and not None, remove characters in chars instead.
If chars is unicode, S will be converted to unicode before stripping
- - -

## str.split
S.split([sep [,maxsplit]]) -> list of strings

Return a list of the words in the string S, using sep as the
delimiter string.  If maxsplit is given, at most maxsplit
splits are done. If sep is not specified or is None, any
whitespace string is a separator and empty strings are removed
from the result.
- - -

## str.splitlines
S.splitlines(keepends=False) -> list of strings

Return a list of the lines in S, breaking at line boundaries.
Line breaks are not included in the resulting list unless keepends
is given and true.
- - -

## str.startswith
S.startswith(prefix[, start[, end]]) -> bool

Return True if S starts with the specified prefix, False otherwise.
With optional start, test S beginning at that position.
With optional end, stop comparing S at that position.
prefix can also be a tuple of strings to try.
- - -

## str.strip
S.strip([chars]) -> string or unicode

Return a copy of the string S with leading and trailing
whitespace removed.
If chars is given and not None, remove characters in chars instead.
If chars is unicode, S will be converted to unicode before stripping
- - -

## str.swapcase
S.swapcase() -> string

Return a copy of the string S with uppercase characters
converted to lowercase and vice versa.
- - -

## str.title
S.title() -> string

Return a titlecased version of S, i.e. words start with uppercase
characters, all remaining cased characters have lowercase.
- - -

## str.translate
S.translate(table [,deletechars]) -> string

Return a copy of the string S, where all characters occurring
in the optional argument deletechars are removed, and the
remaining characters have been mapped through the given
translation table, which must be a string of length 256 or None.
If the table argument is None, no translation is applied and
the operation simply removes the characters in deletechars.
- - -

## str.upper
S.upper() -> string

Return a copy of the string S converted to uppercase.
- - -

## str.zfill
S.zfill(width) -> string

Pad a numeric string S with zeros on the left, to fill a field
of the specified width.  The string S is never truncated.
- - -

