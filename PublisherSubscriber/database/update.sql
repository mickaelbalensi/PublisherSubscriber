/* ALTER TABLE Subscribers
ADD is_paid BOOLEAN NOT NULL DEFAULT FALSE
 */



/* ALTER TABLE Subscriptions
DROP COLUMN is_paid */

UPDATE Subscriptions
SET start_date = "2024-08-29 12:10:00"
WHERE subscriber_id = 2 