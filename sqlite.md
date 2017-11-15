# SQLite Music

## Questions

2.1. ArtistId is called a foreign key because it is the primary key of a different table named Artist and is used to link the Album and Artist tables together.

2.2. The Artist album does not have a column called AlbumId because the purpose of the Artist table is to record artists in the database; specific albums and their indices in the database are irrelevant
to the Artist album.

2.3. We still want to use an integer as the primary key for Customer because integers are much more compact and takes up less memory than characters in an email address. Integers can also be autoincremented easily. Moreover, using email address as the primary key would forbid users from changing their email address. If the primary key is instead an integer CustomerId, we could allow customers to update the email address they would like to link with their account.

2.4. SELECT SUM(Total) FROM Invoice WHERE InvoiceDate BETWEEN '2010-01-01' AND '2010-12-31' GROUP BY CustomerId

2.5. SELECT Name FROM Track WHERE TrackId IN (SELECT TrackId FROM InvoiceLine WHERE InvoiceId IN (SELECT InvoiceId FROM Invoice WHERE CustomerId = 50))

2.6. In Track, instead of Composer, we should list ComposerId; in a new table called Composer, we should have a column for ComposerId and another column for Composer, similar to the Artist table. This way, we can avoid repeating a composer's name in the table Track.


## Debrief

a. I found the notes on Lecture 10 helpful.

b. This question took me 20 minutes.
