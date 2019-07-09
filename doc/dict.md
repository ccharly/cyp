# dict
dict() -> new empty dictionary
dict(mapping) -> new dictionary initialized from a mapping object's
    (key, value) pairs
dict(iterable) -> new dictionary initialized as if via:
    d = {}
    for k, v in iterable:
        d[k] = v
dict(**kwargs) -> new dictionary initialized with the name=value pairs
    in the keyword argument list.  For example:  dict(one=1, two=2)
- - -

## dict.clear
D.clear() -> None.  Remove all items from D.
- - -

## dict.copy
D.copy() -> a shallow copy of D
- - -

## dict.fromkeys
Returns a new dict with keys from iterable and values equal to value.
- - -

## dict.get
D.get(k[,d]) -> D[k] if k in D, else d.  d defaults to None.
- - -

## dict.items
D.items() -> a set-like object providing a view on D's items
- - -

## dict.keys
D.keys() -> a set-like object providing a view on D's keys
- - -

## dict.pop
D.pop(k[,d]) -> v, remove specified key and return the corresponding value.
If key is not found, d is returned if given, otherwise KeyError is raised
- - -

## dict.popitem
D.popitem() -> (k, v), remove and return some (key, value) pair as a
2-tuple; but raise KeyError if D is empty.
- - -

## dict.setdefault
D.setdefault(k[,d]) -> D.get(k,d), also set D[k]=d if k not in D
- - -

## dict.update
D.update([E, ]**F) -> None.  Update D from dict/iterable E and F.
If E is present and has a .keys() method, then does:  for k in E: D[k] = E[k]
If E is present and lacks a .keys() method, then does:  for k, v in E: D[k] = v
In either case, this is followed by: for k in F:  D[k] = F[k]
- - -

## dict.values
D.values() -> an object providing a view on D's values
- - -

