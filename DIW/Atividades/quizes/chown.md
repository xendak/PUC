The system has four users that are assigned to the following groups:

    The consultant1 user is a member of the consultant1 and database1 groups.

    The operator1 user is a member of the operator1 and database1 groups.

    The contractor1 user is a member of the contractor1 and contractor3 groups.

    The operator2 user is a member of the operator2 and contractor3 groups.

The . special directory contains four files with the following permissions:

Question 1:
Which regular file does the operator1 user own and all users can read?

C. db1.conf

db1.conf has permissions -rw-rw-r--, making it readable by all users.

Question 2:
Which file can the contractor1 user modify?

B. app2.log

contractor1 is in the contractor1 and contractor3 groups. db1.conf has group database1 with write permissions, and contractor1 does not belong to the database1 group. Only operator2 would be able to modify db1.conf if they were part of the database1 group, but they are not.

Question 3:
Which file can the operator2 user not read?

D. db2.conf

db2.conf has permissions -rw-r-----, making it unreadable by users not in the database1 group or the operator1 user.

Question 4:
Which file does the consultant1 group own?

A. app1.log

app1.log has group consultant1.

Question 5:
Which files can the operator1 user delete?

C. All the files in the directory

operator1 has write and execute permissions on the directory . and thus can delete files within it.

Question 6:
Which files can the operator2 user delete?

D. None of the files

operator2 does not have permissions to write to the directory . and cannot delete files within it.
