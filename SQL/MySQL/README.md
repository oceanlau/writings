# MySQL

## Type

- char, varchar(50)
- int(20)

## Locking and Transaction (InnoDB)

- ACID
  - Atomicity: all succeed or all fail.
  - Consistency: property of the application. Some invariants must always hold.
  - Isolation: dealing with concurrency. Don't lose update.
  - Durability: safety of data.

- BASE (Basically Available, Soft state, Eventual consistency)

- Basic Locks:
  - Shared lock: granted immediately unless there is an exclusive lock. Used to read.
  - Exclusive lock: granted after all shared locks and exclusive locks are released. Used to update or delete.

- Isolation levels: From loose to strict: READ UNCOMMITTED, READ COMMITTED, REPEATABLE READ (InnoDB default), and SERIALIZABLE


## Indexes (B-tree)

Ref: [https://dev.mysql.com/doc/refman/8.0/en/mysql-indexes.html](https://dev.mysql.com/doc/refman/8.0/en/mysql-indexes.html)

- Types: PRIMARY KEY, UNIQUE, INDEX, and FULLTEXT (in new versions). Most are B-trees. Spatial data indexes use R-trees. MEMORY tables use B-trees or hash indexes. InnoDB uses inverted lists for FULLTEXT indexes.
- Choosing index: Prefer the most selective index (index that finds the smallest number of rows) when multiple indexes can be used.
- If the table has a multiple-column index, any leftmost prefix of the index can be used by the optimizer to look up rows.
- Covering index: If a query uses from a table only columns that are included in some index, the selected values can be retrieved from the index tree.
- In InnoDB table, primary key is implicitly part of any index. (?)
- Clustered index: row stored inside the index. InnoDB primary key default.

### WHERE

- Index is used only when a prefix of the index is present in all sub `AND` clauses:

```SQL
# INDEX idx (k1, k2, k3)
... WHERE k1=1 AND k2=2 AND A=3
... WHERE k1=1 OR A=10 AND k1=2
... WHERE k1=1 AND k3=2 # only k1 used
... WHERE k1=1 AND k2=2 OR k1=3 AND k3=3; # only k1 used. k2 is not!

# The following do not use index
... WHERE k2=1 AND k3=2 # Not prefix
... WHERE k1=1 OR A=10 # Not present in all sub `AND` clauses
... WHERE k1=1 OR k2=10 # Also not present in all sub `AND` clauses!

```
- `LIKE` statement: Index is used if the argument to `LIKE` is a constant string that does not start with a wildcard character:

```SQL
# INDEX idx (k1)
... WHERE k1 LIKE 'Patrick%';
... WHERE k1 LIKE 'Pat%_ck%';

# The following do not use index
... WHERE k1 LIKE '%Patrick%';
... WHERE k1 LIKE other_col;
```

### ORDER BY

Ref: [https://dev.mysql.com/doc/refman/8.0/en/order-by-optimization.html](https://dev.mysql.com/doc/refman/8.0/en/order-by-optimization.html)

#### Uses Index

- All the columns selected are in the `ORDER BY` clause. No `WHERE` clause. Also the orders of the columns requested in the `ORDER BY` clause are the same or the opposite of index columns:

```SQL
# INDEX idx (k1 DESC, k2 ASC)
SELECT k1, k2 FROM t1 ORDER BY k1 DESC, k2 ASC;
SELECT k1, k2 FROM t1 ORDER BY k1 ASC, k2 DESC;
```

- `WHERE` clause uses leftmost prefix of index and are the same as the `ORDER BY` clause. But optimizer may still choose table scan if the `WHERE` clause are not selective at all.

```SQL
# INDEX idx (k1, k2)
SELECT k1, k2 FROM t1 WHERE k1 = constant ORDER BY k1;

SELECT k1, k2 FROM t1 WHERE k1 > constant ORDER BY k1 ASC;
SELECT k1, k2 FROM t1 WHERE k1 < constant ORDER BY k1 DESC;
```

#### May Use Index

- `WHERE` clause uses leftmost prefix of index but are not same as the `ORDER BY` clause. Optimizer may use index if the different prefix columns are constant.

```SQL
# INDEX idx (k1, k2)
SELECT k1, k2 FROM t1 WHERE k1 = constant ORDER BY k2;
SELECT k1, k2 FROM t1 WHERE k1 = constant AND k2 > constant ORDER BY k2;
```

- Columns selected are not in the `ORDER BY` clause. Read the entire index and then looking up table rows might be more expensive than just read the whole table and sort. So optimizer may or may not use index.

```SQL
# INDEX idx (k1, k2)
SELECT * FROM t1 ORDER BY k1, k2;
```

#### Will Not Use Index

- `ORDER BY` columns from multiple indexes or are different from `WHERE` columns or are different from `GROUP BY` columns.
- `ORDER BY` nonconsecutive parts of an index.

### Comparing with Hash Index

- B-tree is ordered and hash index is not. So B-tree supports comparison operators while hash index only supports equality. Also B-tree can be used to speed up `ORDER BY` while hash index can not.
- Leftmost prefixes of B-tree index are still indexes. Hash index can only use whole key.

### Comparing InnoDB and MyISAM

- InnoDB has row-level locking. MyISAM only has full table-level locking.
- InnoDB supports transactions, which means you can commit and roll back. MyISAM does not.
- ...

The only MyISAM advantages left are:

- Tables will be smaller on disk compared to uncompressed InnoDB tables.
- The count(\*) is still much faster in MyISAM. There is a counter inside.

## Some Details

- mysqldump
- binlog