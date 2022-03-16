# Reg Commands

Performs operations on registry subkey information and values in registry entries.

Some operations enable you to view or configure registry entries on local or remote computers, while others allow you to configure only local computers. Using reg to configure the registry of remote computers limits the parameters that you can use in some operations. Check the syntax and parameters for each operation to verify that they can be used on remote computers.

> **Caution**<br>Don't edit the registry directly unless you have no alternative. The registry editor bypasses standard safeguards, allowing settings that can degrade performance, damage your system, or even require you to reinstall Windows. You can safely alter most registry settings by using the programs in Control Panel or Microsoft Management Console (MMC). If you must edit the registry directly, back it up first.

## Syntax

```
reg add
reg compare
reg copy
reg delete
reg export
reg import
reg load
reg query
reg restore
reg save
reg unload
```

## Parameters

Parameter | Description
--- | ---
reg add | Adds a new subkey or entry to the registry.
reg compare | Compares specified registry subkeys or entries.
reg copy | Copies a registry entry to a specified location on the local or remote computer.
reg delete | Deletes a subkey or entries from the registry.
reg export | Copies the specified subkeys, entries, and values of the local computer into a file for transfer to other servers.
reg import | Copies the contents of a file that contains exported registry subkeys, entries, and values into the registry of the local computer.
reg load | Writes saved subkeys and entries into a different subkey in the registry.
reg query | Returns a list of the next tier of subkeys and entries that are located under a specified subkey in the registry.
reg restore | Writes saved subkeys and entries back to the registry.
reg save | Saves a copy of specified subkeys, entries, and values of the registry in a specified file.
reg unload | Removes a section of the registry that was loaded using the reg load operation.

## Additional References

* Command-Line Syntax Key