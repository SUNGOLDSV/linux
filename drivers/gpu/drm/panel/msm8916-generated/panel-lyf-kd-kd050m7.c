// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2021 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2013, The Linux Foundation. All rights reserved. (FIXME)

#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/module.h>
#include <linux/of.h>

#include <video/mipi_display.h>

#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>

struct kd050m7_kd {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct gpio_desc *reset_gpio;
	bool prepared;
};

static inline struct kd050m7_kd *to_kd050m7_kd(struct drm_panel *panel)
{
	return container_of(panel, struct kd050m7_kd, panel);
}

#define dsi_dcs_write_seq(dsi, seq...) do {				\
		static const u8 d[] = { seq };				\
		int ret;						\
		ret = mipi_dsi_dcs_write_buffer(dsi, d, ARRAY_SIZE(d));	\
		if (ret < 0)						\
			return ret;					\
	} while (0)

static void kd050m7_kd_reset(struct kd050m7_kd *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	msleep(20);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(2000, 3000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	msleep(20);
}

static int kd050m7_kd_on(struct kd050m7_kd *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;
	struct device *dev = &dsi->dev;
	int ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	dsi_dcs_write_seq(dsi, 0xe0, 0x00);
	dsi_dcs_write_seq(dsi, 0xe1, 0x93);
	dsi_dcs_write_seq(dsi, 0xe2, 0x65);
	dsi_dcs_write_seq(dsi, 0xe3, 0xf8);
	dsi_dcs_write_seq(dsi, 0xe0, 0x04);
	dsi_dcs_write_seq(dsi, MIPI_DCS_WRITE_LUT, 0x03);
	dsi_dcs_write_seq(dsi, 0x2b, 0x2b);
	dsi_dcs_write_seq(dsi, MIPI_DCS_READ_MEMORY_START, 0x44);
	dsi_dcs_write_seq(dsi, 0xe0, 0x00);
	dsi_dcs_write_seq(dsi, MIPI_DCS_WRITE_POWER_SAVE, 0x00);
	dsi_dcs_write_seq(dsi, 0xe6, 0x02);
	dsi_dcs_write_seq(dsi, 0xe7, 0x02);
	dsi_dcs_write_seq(dsi, 0x70, 0x10);
	dsi_dcs_write_seq(dsi, 0x71, 0x13);
	dsi_dcs_write_seq(dsi, 0x72, 0x06);
	dsi_dcs_write_seq(dsi, 0x75, 0x03);
	dsi_dcs_write_seq(dsi, 0xe0, 0x01);
	dsi_dcs_write_seq(dsi, 0x00, 0x00);
	dsi_dcs_write_seq(dsi, 0x01, 0xc7);
	dsi_dcs_write_seq(dsi, 0x03, 0x00);
	dsi_dcs_write_seq(dsi, 0x04, 0x9f);
	dsi_dcs_write_seq(dsi, 0x0a, 0x07);
	dsi_dcs_write_seq(dsi, 0x0c, 0x74);
	dsi_dcs_write_seq(dsi, 0x17, 0x00);
	dsi_dcs_write_seq(dsi, 0x18, 0xe7);
	dsi_dcs_write_seq(dsi, 0x19, 0x01);
	dsi_dcs_write_seq(dsi, 0x1a, 0x00);
	dsi_dcs_write_seq(dsi, 0x1b, 0xe7);
	dsi_dcs_write_seq(dsi, 0x1c, 0x01);
	dsi_dcs_write_seq(dsi, 0x1f, 0x3e);
	dsi_dcs_write_seq(dsi, 0x20, 0x3d);
	dsi_dcs_write_seq(dsi, 0x21, 0x3d);
	dsi_dcs_write_seq(dsi, 0x22, 0xf8);
	dsi_dcs_write_seq(dsi, 0x37, 0x09);
	dsi_dcs_write_seq(dsi, 0x38, 0x04);
	dsi_dcs_write_seq(dsi, 0x39, 0x08);

	ret = mipi_dsi_dcs_set_pixel_format(dsi, 0x12);
	if (ret < 0) {
		dev_err(dev, "Failed to set pixel format: %d\n", ret);
		return ret;
	}

	dsi_dcs_write_seq(dsi, MIPI_DCS_WRITE_MEMORY_CONTINUE, 0x78);
	dsi_dcs_write_seq(dsi, MIPI_DCS_READ_MEMORY_CONTINUE, 0xff);
	dsi_dcs_write_seq(dsi, MIPI_DCS_READ_MEMORY_CONTINUE, 0xff);
	dsi_dcs_write_seq(dsi, 0x3f, 0xff);
	dsi_dcs_write_seq(dsi, MIPI_DCS_SET_VSYNC_TIMING, 0x04);
	dsi_dcs_write_seq(dsi, 0x41, 0xa0);
	dsi_dcs_write_seq(dsi, 0x43, 0x09);
	dsi_dcs_write_seq(dsi, 0x44, 0x07);
	dsi_dcs_write_seq(dsi, MIPI_DCS_GET_SCANLINE, 0x30);
	dsi_dcs_write_seq(dsi, MIPI_DCS_WRITE_POWER_SAVE, 0x01);
	dsi_dcs_write_seq(dsi, 0x56, 0x01);
	dsi_dcs_write_seq(dsi, 0x57, 0x69);
	dsi_dcs_write_seq(dsi, 0x58, 0x0a);
	dsi_dcs_write_seq(dsi, 0x59, 0x0a);
	dsi_dcs_write_seq(dsi, 0x5a, 0x2a);
	dsi_dcs_write_seq(dsi, 0x5b, 0x1b);
	dsi_dcs_write_seq(dsi, 0x5c, 0x16);
	dsi_dcs_write_seq(dsi, 0x5d, 0x7f);
	dsi_dcs_write_seq(dsi, MIPI_DCS_SET_CABC_MIN_BRIGHTNESS, 0x48);
	dsi_dcs_write_seq(dsi, 0x5f, 0x36);
	dsi_dcs_write_seq(dsi, 0x60, 0x29);
	dsi_dcs_write_seq(dsi, 0x61, 0x24);
	dsi_dcs_write_seq(dsi, 0x62, 0x16);
	dsi_dcs_write_seq(dsi, 0x63, 0x1b);
	dsi_dcs_write_seq(dsi, 0x64, 0x05);
	dsi_dcs_write_seq(dsi, 0x65, 0x1d);
	dsi_dcs_write_seq(dsi, 0x66, 0x1b);
	dsi_dcs_write_seq(dsi, 0x67, 0x1a);
	dsi_dcs_write_seq(dsi, 0x68, 0x38);
	dsi_dcs_write_seq(dsi, 0x69, 0x29);
	dsi_dcs_write_seq(dsi, 0x6a, 0x33);
	dsi_dcs_write_seq(dsi, 0x6b, 0x35);
	dsi_dcs_write_seq(dsi, 0x6c, 0x24);
	dsi_dcs_write_seq(dsi, 0x6d, 0x1a);
	dsi_dcs_write_seq(dsi, 0x6e, 0x12);
	dsi_dcs_write_seq(dsi, 0x6f, 0x01);
	dsi_dcs_write_seq(dsi, 0x70, 0x7f);
	dsi_dcs_write_seq(dsi, 0x71, 0x48);
	dsi_dcs_write_seq(dsi, 0x72, 0x36);
	dsi_dcs_write_seq(dsi, 0x73, 0x29);
	dsi_dcs_write_seq(dsi, 0x74, 0x24);
	dsi_dcs_write_seq(dsi, 0x75, 0x16);
	dsi_dcs_write_seq(dsi, 0x76, 0x1b);
	dsi_dcs_write_seq(dsi, 0x77, 0x05);
	dsi_dcs_write_seq(dsi, 0x78, 0x1d);
	dsi_dcs_write_seq(dsi, 0x79, 0x1a);
	dsi_dcs_write_seq(dsi, 0x7a, 0x1a);
	dsi_dcs_write_seq(dsi, 0x7b, 0x36);
	dsi_dcs_write_seq(dsi, 0x7c, 0x24);
	dsi_dcs_write_seq(dsi, 0x7d, 0x2e);
	dsi_dcs_write_seq(dsi, 0x7e, 0x20);
	dsi_dcs_write_seq(dsi, 0x7f, 0x24);
	dsi_dcs_write_seq(dsi, 0x80, 0x1a);
	dsi_dcs_write_seq(dsi, 0x81, 0x12);
	dsi_dcs_write_seq(dsi, 0x82, 0x01);
	dsi_dcs_write_seq(dsi, 0xe0, 0x02);
	dsi_dcs_write_seq(dsi, 0x00, 0x00);
	dsi_dcs_write_seq(dsi, 0x01, 0x04);
	dsi_dcs_write_seq(dsi, 0x02, 0x06);
	dsi_dcs_write_seq(dsi, 0x03, 0x08);
	dsi_dcs_write_seq(dsi, 0x04, 0x0a);
	dsi_dcs_write_seq(dsi, 0x05, 0x1f);
	dsi_dcs_write_seq(dsi, 0x06, 0x1f);
	dsi_dcs_write_seq(dsi, 0x07, 0x1f);
	dsi_dcs_write_seq(dsi, 0x08, 0x1f);
	dsi_dcs_write_seq(dsi, 0x09, 0x1f);
	dsi_dcs_write_seq(dsi, 0x0a, 0x1f);
	dsi_dcs_write_seq(dsi, 0x0b, 0x1f);
	dsi_dcs_write_seq(dsi, 0x0c, 0x1f);
	dsi_dcs_write_seq(dsi, 0x0d, 0x1f);
	dsi_dcs_write_seq(dsi, 0x0e, 0x1f);
	dsi_dcs_write_seq(dsi, 0x0f, 0x1e);
	dsi_dcs_write_seq(dsi, 0x10, 0x1e);
	dsi_dcs_write_seq(dsi, 0x11, 0x1e);
	dsi_dcs_write_seq(dsi, 0x12, 0x1f);
	dsi_dcs_write_seq(dsi, 0x13, 0x1e);
	dsi_dcs_write_seq(dsi, 0x14, 0x1f);
	dsi_dcs_write_seq(dsi, 0x15, 0x10);
	dsi_dcs_write_seq(dsi, 0x16, 0x01);
	dsi_dcs_write_seq(dsi, 0x17, 0x05);
	dsi_dcs_write_seq(dsi, 0x18, 0x07);
	dsi_dcs_write_seq(dsi, 0x19, 0x09);
	dsi_dcs_write_seq(dsi, 0x1a, 0x0b);
	dsi_dcs_write_seq(dsi, 0x1b, 0x1f);
	dsi_dcs_write_seq(dsi, 0x1c, 0x1f);
	dsi_dcs_write_seq(dsi, 0x1d, 0x1f);
	dsi_dcs_write_seq(dsi, 0x1e, 0x1f);
	dsi_dcs_write_seq(dsi, 0x1f, 0x1f);
	dsi_dcs_write_seq(dsi, 0x20, 0x1f);
	dsi_dcs_write_seq(dsi, 0x21, 0x1f);
	dsi_dcs_write_seq(dsi, 0x22, 0x1f);
	dsi_dcs_write_seq(dsi, 0x23, 0x1f);
	dsi_dcs_write_seq(dsi, 0x24, 0x1f);
	dsi_dcs_write_seq(dsi, 0x25, 0x1e);
	dsi_dcs_write_seq(dsi, MIPI_DCS_SET_GAMMA_CURVE, 0x1e);
	dsi_dcs_write_seq(dsi, 0x27, 0x1e);
	dsi_dcs_write_seq(dsi, 0x28, 0x1f);
	dsi_dcs_write_seq(dsi, 0x29, 0x1e);
	dsi_dcs_write_seq(dsi, 0x2a, 0x1f);
	dsi_dcs_write_seq(dsi, 0x2b, 0x11);
	dsi_dcs_write_seq(dsi, MIPI_DCS_WRITE_MEMORY_START, 0x11);
	dsi_dcs_write_seq(dsi, MIPI_DCS_WRITE_LUT, 0x0b);
	dsi_dcs_write_seq(dsi, MIPI_DCS_READ_MEMORY_START, 0x09);
	dsi_dcs_write_seq(dsi, 0x2f, 0x07);
	dsi_dcs_write_seq(dsi, MIPI_DCS_SET_PARTIAL_ROWS, 0x05);
	dsi_dcs_write_seq(dsi, MIPI_DCS_SET_PARTIAL_COLUMNS, 0x1f);
	dsi_dcs_write_seq(dsi, 0x32, 0x1f);
	dsi_dcs_write_seq(dsi, 0x33, 0x1f);
	dsi_dcs_write_seq(dsi, 0x34, 0x1f);
	dsi_dcs_write_seq(dsi, 0x35, 0x1f);
	dsi_dcs_write_seq(dsi, MIPI_DCS_SET_ADDRESS_MODE, 0x1f);
	dsi_dcs_write_seq(dsi, 0x37, 0x1f);
	dsi_dcs_write_seq(dsi, 0x38, 0x1f);
	dsi_dcs_write_seq(dsi, 0x39, 0x1f);

	ret = mipi_dsi_dcs_set_pixel_format(dsi, 0x1f);
	if (ret < 0) {
		dev_err(dev, "Failed to set pixel format: %d\n", ret);
		return ret;
	}

	dsi_dcs_write_seq(dsi, 0x3b, 0x1e);
	dsi_dcs_write_seq(dsi, MIPI_DCS_WRITE_MEMORY_CONTINUE, 0x1e);
	dsi_dcs_write_seq(dsi, MIPI_DCS_SET_3D_CONTROL, 0x1e);
	dsi_dcs_write_seq(dsi, MIPI_DCS_READ_MEMORY_CONTINUE, 0x1f);
	dsi_dcs_write_seq(dsi, 0x3f, 0x1f);
	dsi_dcs_write_seq(dsi, MIPI_DCS_SET_VSYNC_TIMING, 0x1e);
	dsi_dcs_write_seq(dsi, 0x41, 0x01);
	dsi_dcs_write_seq(dsi, 0x42, 0x10);
	dsi_dcs_write_seq(dsi, 0x43, 0x0a);
	dsi_dcs_write_seq(dsi, 0x44, 0x08);
	dsi_dcs_write_seq(dsi, MIPI_DCS_GET_SCANLINE, 0x06);
	dsi_dcs_write_seq(dsi, 0x46, 0x04);
	dsi_dcs_write_seq(dsi, 0x47, 0x1f);
	dsi_dcs_write_seq(dsi, 0x48, 0x1f);
	dsi_dcs_write_seq(dsi, 0x49, 0x1f);
	dsi_dcs_write_seq(dsi, 0x4a, 0x1f);
	dsi_dcs_write_seq(dsi, 0x4b, 0x1f);
	dsi_dcs_write_seq(dsi, 0x4c, 0x1f);
	dsi_dcs_write_seq(dsi, 0x4d, 0x1f);
	dsi_dcs_write_seq(dsi, 0x4e, 0x1f);
	dsi_dcs_write_seq(dsi, 0x4f, 0x1f);
	dsi_dcs_write_seq(dsi, 0x50, 0x1f);

	ret = mipi_dsi_dcs_set_display_brightness(dsi, 0x001e);
	if (ret < 0) {
		dev_err(dev, "Failed to set display brightness: %d\n", ret);
		return ret;
	}

	dsi_dcs_write_seq(dsi, 0x52, 0x1e);
	dsi_dcs_write_seq(dsi, MIPI_DCS_WRITE_CONTROL_DISPLAY, 0x1e);
	dsi_dcs_write_seq(dsi, 0x54, 0x1f);
	dsi_dcs_write_seq(dsi, MIPI_DCS_WRITE_POWER_SAVE, 0x1f);
	dsi_dcs_write_seq(dsi, 0x56, 0x1e);
	dsi_dcs_write_seq(dsi, 0x57, 0x00);
	dsi_dcs_write_seq(dsi, 0x58, 0x00);
	dsi_dcs_write_seq(dsi, 0x59, 0x00);
	dsi_dcs_write_seq(dsi, 0x5a, 0x00);
	dsi_dcs_write_seq(dsi, 0x5b, 0x10);
	dsi_dcs_write_seq(dsi, 0x5c, 0x01);
	dsi_dcs_write_seq(dsi, 0x5d, 0x30);
	dsi_dcs_write_seq(dsi, MIPI_DCS_SET_CABC_MIN_BRIGHTNESS, 0x01);
	dsi_dcs_write_seq(dsi, 0x5f, 0x02);
	dsi_dcs_write_seq(dsi, 0x60, 0x30);
	dsi_dcs_write_seq(dsi, 0x61, 0x01);
	dsi_dcs_write_seq(dsi, 0x62, 0x02);
	dsi_dcs_write_seq(dsi, 0x63, 0x03);
	dsi_dcs_write_seq(dsi, 0x64, 0x6b);
	dsi_dcs_write_seq(dsi, 0x65, 0x55);
	dsi_dcs_write_seq(dsi, 0x66, 0x0b);
	dsi_dcs_write_seq(dsi, 0x67, 0x73);
	dsi_dcs_write_seq(dsi, 0x68, 0x07);
	dsi_dcs_write_seq(dsi, 0x69, 0x06);
	dsi_dcs_write_seq(dsi, 0x6a, 0x6b);
	dsi_dcs_write_seq(dsi, 0x6b, 0x00);
	dsi_dcs_write_seq(dsi, 0x6c, 0x00);
	dsi_dcs_write_seq(dsi, 0x6d, 0x04);
	dsi_dcs_write_seq(dsi, 0x6e, 0x04);
	dsi_dcs_write_seq(dsi, 0x6f, 0x88);
	dsi_dcs_write_seq(dsi, 0x70, 0x00);
	dsi_dcs_write_seq(dsi, 0x71, 0x00);
	dsi_dcs_write_seq(dsi, 0x72, 0x06);
	dsi_dcs_write_seq(dsi, 0x73, 0x7b);
	dsi_dcs_write_seq(dsi, 0x74, 0x00);
	dsi_dcs_write_seq(dsi, 0x75, 0x87);
	dsi_dcs_write_seq(dsi, 0x76, 0x00);
	dsi_dcs_write_seq(dsi, 0x77, 0x5d);
	dsi_dcs_write_seq(dsi, 0x78, 0x18);
	dsi_dcs_write_seq(dsi, 0x79, 0x1f);
	dsi_dcs_write_seq(dsi, 0x7a, 0x00);
	dsi_dcs_write_seq(dsi, 0x7b, 0x00);
	dsi_dcs_write_seq(dsi, 0x7c, 0x00);
	dsi_dcs_write_seq(dsi, 0x7d, 0x03);
	dsi_dcs_write_seq(dsi, 0x7e, 0x7b);
	dsi_dcs_write_seq(dsi, 0xe0, 0x04);
	dsi_dcs_write_seq(dsi, 0x09, 0x10);
	dsi_dcs_write_seq(dsi, 0x2b, 0x2b);
	dsi_dcs_write_seq(dsi, MIPI_DCS_READ_MEMORY_START, 0x44);
	dsi_dcs_write_seq(dsi, 0xe0, 0x00);
	dsi_dcs_write_seq(dsi, 0xe6, 0x02);
	dsi_dcs_write_seq(dsi, 0xe7, 0x02);

	ret = mipi_dsi_dcs_exit_sleep_mode(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to exit sleep mode: %d\n", ret);
		return ret;
	}
	msleep(120);

	ret = mipi_dsi_dcs_set_display_on(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to set display on: %d\n", ret);
		return ret;
	}
	msleep(20);

	return 0;
}

static int kd050m7_kd_off(struct kd050m7_kd *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;
	struct device *dev = &dsi->dev;
	int ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_set_display_off(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to set display off: %d\n", ret);
		return ret;
	}
	msleep(50);

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to enter sleep mode: %d\n", ret);
		return ret;
	}
	msleep(120);

	return 0;
}

static int kd050m7_kd_prepare(struct drm_panel *panel)
{
	struct kd050m7_kd *ctx = to_kd050m7_kd(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	if (ctx->prepared)
		return 0;

	kd050m7_kd_reset(ctx);

	ret = kd050m7_kd_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		return ret;
	}

	ctx->prepared = true;
	return 0;
}

static int kd050m7_kd_unprepare(struct drm_panel *panel)
{
	struct kd050m7_kd *ctx = to_kd050m7_kd(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	if (!ctx->prepared)
		return 0;

	ret = kd050m7_kd_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);

	ctx->prepared = false;
	return 0;
}

static const struct drm_display_mode kd050m7_kd_mode = {
	.clock = (720 + 24 + 24 + 24) * (1280 + 16 + 4 + 6) * 60 / 1000,
	.hdisplay = 720,
	.hsync_start = 720 + 24,
	.hsync_end = 720 + 24 + 24,
	.htotal = 720 + 24 + 24 + 24,
	.vdisplay = 1280,
	.vsync_start = 1280 + 16,
	.vsync_end = 1280 + 16 + 4,
	.vtotal = 1280 + 16 + 4 + 6,
	.width_mm = 63,
	.height_mm = 111,
};

static int kd050m7_kd_get_modes(struct drm_panel *panel,
				struct drm_connector *connector)
{
	struct drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &kd050m7_kd_mode);
	if (!mode)
		return -ENOMEM;

	drm_mode_set_name(mode);

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;
	drm_mode_probed_add(connector, mode);

	return 1;
}

static const struct drm_panel_funcs kd050m7_kd_panel_funcs = {
	.prepare = kd050m7_kd_prepare,
	.unprepare = kd050m7_kd_unprepare,
	.get_modes = kd050m7_kd_get_modes,
};

static int kd050m7_kd_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct kd050m7_kd *ctx;
	int ret;

	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(ctx->reset_gpio))
		return dev_err_probe(dev, PTR_ERR(ctx->reset_gpio),
				     "Failed to get reset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_drvdata(dsi, ctx);

	dsi->lanes = 4;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_MODE_VIDEO_HSE | MIPI_DSI_MODE_EOT_PACKET |
			  MIPI_DSI_CLOCK_NON_CONTINUOUS;

	drm_panel_init(&ctx->panel, dev, &kd050m7_kd_panel_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	ret = drm_panel_of_backlight(&ctx->panel);
	if (ret)
		return dev_err_probe(dev, ret, "Failed to get backlight\n");

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to attach to DSI host: %d\n", ret);
		drm_panel_remove(&ctx->panel);
		return ret;
	}

	return 0;
}

static int kd050m7_kd_remove(struct mipi_dsi_device *dsi)
{
	struct kd050m7_kd *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);

	return 0;
}

static const struct of_device_id kd050m7_kd_of_match[] = {
	{ .compatible = "lyf,kd-kd050m7" }, // FIXME
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, kd050m7_kd_of_match);

static struct mipi_dsi_driver kd050m7_kd_driver = {
	.probe = kd050m7_kd_probe,
	.remove = kd050m7_kd_remove,
	.driver = {
		.name = "panel-kd050m7-kd",
		.of_match_table = kd050m7_kd_of_match,
	},
};
module_mipi_dsi_driver(kd050m7_kd_driver);

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator <fix@me>"); // FIXME
MODULE_DESCRIPTION("DRM driver for kd kd050m7 hd video mode dsi panel");
MODULE_LICENSE("GPL v2");
