# Tree command

Displays the directory structure of a path or of the disk in a drive graphically. The structure displayed by this command depends upon the parameters that you specify at the command prompt. If you don't specify a drive or path, this command displays the tree structure beginning with the current directory of the current drive.

## Syntax

```
tree [<drive>:][<path>] [/f] [/a]
```

## Parameters

Parameter|Description
---|---
`<drive>:`|Specifies the drive that contains the disk for which you want to display the directory structure.
`<path>`|Specifies the directory for which you want to display the directory structure.
`/f`|Displays the names of the files in each directory.
`/a`|Specifies to use text characters instead of graphic characters to show the lines that link subdirectories.
`/?`|Displays help at the command prompt.

## Examples

To display the names of all the subdirectories on the disk in your current drive, type:

```
tree \
```

To display, one screen at a time, the files in all the directories on drive C, type:

```
tree c:\ /f | more
```

To print a list of all the directories on drive C, type:

```
tree c:\ /f  prn
```

## Additional References

* Command-Line Syntax Key
