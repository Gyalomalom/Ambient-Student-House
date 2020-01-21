# Arduino

## Code Structure

* code structure good and readable.

## Code Quality (naming, comments)

* very good comments in smoke detector
* good debouncing
* Code formatting could be better (Ctr-T anyone?)
* Servo rotary has magic numbers @ line: 45,46 etc.

# Windows


## Code Structure

* All code in a single class. Why not create a Room class etc.
* Is all functionality supported? Code seems to be lacking.

## code Quality (naming, comments)

* Not enough comments.

# Protocol

* Fan serial protocol relies on timeouts for ending message. Use a start and end marker char instead.


