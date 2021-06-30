/* SPDX-License-Identifier: BSD-2-Clause */
/* X-SPDX-Copyright-Text: (c) Copyright 2021 Xilinx, Inc. */
#ifndef	EFCT_HW_DEFS_H
#define	EFCT_HW_DEFS_H

#include <ci/driver/efab/hardware/efct.h>

/* The following definitions aren't hardware-specific, but they do describe
 * low-level contraints and properties of the efhw interface */

/* Max superbufs permitted to be assigned to a single rxq, across the whole
 * system. Can be adjusted at whim, but affects the size of preallocated
 * arrays in various places. Most notably the enormous address space
 * reservation done by ef_vi. */
#define CI_EFCT_MAX_SUPERBUFS   512

/* As defined by the CPU architecture */
#define CI_HUGEPAGE_SIZE   2097152

#define CI_EFCT_SUPERBUFS_PER_PAGE (CI_HUGEPAGE_SIZE / EFCT_RX_SUPERBUF_BYTES)
#define CI_EFCT_MAX_HUGEPAGES \
                          (CI_EFCT_MAX_SUPERBUFS / CI_EFCT_SUPERBUFS_PER_PAGE)

/* Mask of efct_rx_superbuf_queue::q values to get the actual superbuf ID (the
 * top bit is use in the rxq to convey the sentinel). */
#define CI_EFCT_Q_SUPERBUF_ID_MASK  0x7fff

struct efab_efct_rx_superbuf_queue {
  uint16_t q[16];
  uint64_t added CI_ALIGN(8);
  uint32_t removed;
};

struct efab_efct_rxq_uk_shm {
  struct efab_efct_rx_superbuf_queue rxq;
  struct efab_efct_rx_superbuf_queue freeq;
  uint64_t timestamp_hi CI_ALIGN(8);
  unsigned config_generation;
  struct {
    unsigned no_rxq_space;
    unsigned too_many_owned;
  } stats;
};

#endif /* EFCT_HW_DEFS_H */