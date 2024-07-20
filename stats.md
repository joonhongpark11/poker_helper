# Poker Hand Probabilities (Texas Holdem)

### Probabilities for Each Hand (7 out of 52 cards)

| Hand            | Number of Cases         | Probability (%)  | Odds         |
|:---------------:|:-----------------------:|:----------------:|:------------:|
| Royal Flush     | 4324                    | 0.003232062      | 30939:1      |
| Straight Flush  | 37260                   | 0.027850748      | 3589.57:1    |
| Four-of-a-kind  | 224848                  | 0.168067227      | 594:1        |
| Full House      | 3473184                 | 2.596102271      | 37.52:1      |
| Flush           | 4047644                 | 3.025494123      | 32.05:1      |
| Straight        | 6180020                 | 4.619382087      | 20.65:1      |
| Three-of-a-kind | 6461620                 | 4.829869755      | 19.7:1       |
| Two pair        | 31433400                | 23.49553641      | 3.26:1       |
| Pair            | 58627800                | 43.82254574      | 1.28:1       |
| High card       | 23294460                | 17.41191958      | 4.74:1       |


* <b>Total Number of Cases:</b><br>
The total number of possible 7-card hands: $ C(52, 7) = 133,784,560 $

* <b>Royal Flush:</b><br>
There are four ways (Spade, Clover, Heart, Diamond) = 4.<br>
Choosing 2 cards from the remaining 47 cards: $ C(47, 2)$<br>
$$ 4 \times C(47, 2) = 4,324$$

* <b>Straight Flush:</b><br>
9 straight ranks for each suit; (A-5) to (9-K). We are excluding Royal Flush(10-A).<br>
There are four suits possible.
Need to choose 2 cards from remaining 47 cards. However, if we choose a card one above the highest of five, it will double count the higher case. So we should exclude the one above the highest of five. $C(46, 2)$.
$$ 9 \times 4 \times C(46, 2) = 37,260$$

* <b>Four-of-a-kind:</b><br>
Choosing one number: $C(13,1)$<br>
Choosing rest 3 cards from remaining 48 cards: $C(48,3)$
$$C(13,1) \times C(48,3) = 224,848$$

* <b>Full House:</b><br>
There are three possible ways. 
1. Three/Three/one<br>
Choose two numbers for rhrees. $C(13,2)$<br>
Choose three suits for each number. $C(4,3)^2$<br>
Choose one card from other numbers. $C(44,1)$
2. Three/Two/Two
Choose number for three. $C(13,1)$<br>
Choose three suits. $C(4,3)$<br>
Choose two numbers for twos. $C(12,2)$<br>
Choose two suits. $C(4,2)^2$

3. Three/Two/One/One <br>
Choose number for three. $C(13,1)$<br>
Choose three suits. $C(4,3)$<br>
Choose number for Two. $C(12,1)$<br>
Choose two suits. $C(4,2)$
Choose numbers for one. $C(11,2)$<br>
Choose one suits. $C(4,1)^2$

$$C(13,2) \times C(4,3)^2 \times C(44,1) \\ + C(13,1) \times C(4,3) \times C(12,2) \times C(4,2)^2 \\ + C(13,1) \times C(4,3) \times C(12,1) \times C(4,2) \times C(11,2) \times C(4,1)^2 \\ = 3,473,184$$
