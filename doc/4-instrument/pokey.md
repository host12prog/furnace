# Atari POKEY instrument editor

the POKEY instrument editor consists of two tabs.

## POKEY

- **16-bit raw period macro**: makes Raw Period macro to go from `0` to `65535`.

## Macros

- **Volume**: volume sequence.
- **Arpeggio**: pitch sequence.
- **AUDCTL**: audio control register sequence:
  - **poly9**: reduces size of LFSR. only on noise waveforms!
  - **high1**: runs channel 1 at 1.79MHz.
  - **high3**: runs channel 3 at 1.79MHz.
  - **16-bit 1+2**: enables 16-bit frequency mode by combining channels 1 and 2.
  - **16-bit 3+4**: enables 16-bit frequency mode by combining channels 3 and 4.
  - **filter 1+3**: applies a high-pass "filter" by combining channels 1 and 3.
  - **filter 2+4**: applies a high-pass "filter" by combining channels 2 and 4.
  - **15KHz**: runs channels at 15KHz.
- **Waveform**: wave selection sequence:
  - 0: harsh noise (poly5+17)
  - 1: square buzz (poly5)
  - 2: weird noise (poly4+5)
  - 3: square buzz (poly5)
  - 4: soft noise (poly17)
  - 5: square
  - 6: bass (poly4)
  - 7: buzz (poly4)
- **Pitch**: fine pitch.
- **Raw Period**: directly sets the period register values. the smaller the value, the higher the pitch.
 - use 16-bit mode if you combine channels into 16-bit frequency mode via `AUDCTL` control bits.