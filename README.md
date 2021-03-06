# SokobanC

SokobanC is a great Sokoban written in C!

## Dependencies

We use the SDL (v2), a powerful graphics, game and media library.

We use conan to manage our dependencies, in particular SDL: [https://docs.conan.io/en/latest/getting_started.html](https://docs.conan.io/en/latest/getting_started.html).

You can install conan using python (>3):

```bash
python3 -m pip install conan
```

SDL is not available on the standard conan repository, you have to add the `bincrafters` repository:

```bash
conan remote add bincrafters https://bincrafters.jfrog.io/artifactory/api/conan/public-conan
conan config set general.revisions_enabled=1
```

## Build

```bash
git clone
cd sokobanc
mkdir build
conan install ..
cmake ..
make
(cd bin && ./bin/sokobanc)
```

## Sokoban format

Here is an example level file containing two levels:

```
1
    #####
    #   #
    #$  #
  ###  $##
  #  $ $ #
### # ## #   ######
#   # ## #####  ..#
# $  $          ..#
##### ### #@##  ..#
    #     #########
    #######
~
2
############
#..  #     ###
#..  # $  $  #
#..  #$####  #
#..    @ ##  #
#..  # #  $ ##
###### ##$ $ #
  # $  $ $ $ #
  #    #     #
  ############
~
```

The following symbols are used:

- `#` is a wall
- `$` is a crate
- `.` is a goal
- `*` is a crate on a goal
- `@` is the player
- `+` is the player on a goal

## Credits

Sprite Sheet: 1001.com
