// Copyright 2025-2026 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.

on tile[1]: {
    mclk_98m_debug();

    // i2s_frame_callback_if i_i2s;
    // i2s_frame_master_external_clock(i_i2s, null, 0, null, 0, 32, p_bclk, p_lrclk, clk_audio_bclk);
    i2s_task_wrapper();
    uint32_t mclk_bclk_ratio = 4;
    // configure_clock_src(clk_audio_mclk, p_mclk_in);
    // configure_clock_src_divide(bclk, p_mclk_in, mclk_bclk_ratio >> 1);
    // configure_port_clock_output(p_bclk, bclk);
    // par {
    // }
}