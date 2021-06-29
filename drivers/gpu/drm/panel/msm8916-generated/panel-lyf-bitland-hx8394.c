// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2021 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2013, The Linux Foundation. All rights reserved. (FIXME)

#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/module.h>
#include <linux/of.h>

#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>

struct hx8394_f_bitland {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct gpio_desc *reset_gpio;
	bool prepared;
};

static inline
struct hx8394_f_bitland *to_hx8394_f_bitland(struct drm_panel *panel)
{
	return container_of(panel, struct hx8394_f_bitland, panel);
}

#define dsi_dcs_write_seq(dsi, seq...) do {				\
		static const u8 d[] = { seq };				\
		int ret;						\
		ret = mipi_dsi_dcs_write_buffer(dsi, d, ARRAY_SIZE(d));	\
		if (ret < 0)						\
			return ret;					\
	} while (0)

static void hx8394_f_bitland_reset(struct hx8394_f_bitland *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	msleep(20);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(2000, 3000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	msleep(20);
}

static int hx8394_f_bitland_on(struct hx8394_f_bitland *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;
	struct device *dev = &dsi->dev;
	int ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	dsi_dcs_write_seq(dsi, 0xb9, 0xff, 0x83, 0x94);
	dsi_dcs_write_seq(dsi, 0xba, 0x63, 0x03, 0x68, 0x6b, 0xb2, 0xc0);
	dsi_dcs_write_seq(dsi, 0xb1,
			  0x50, 0x12, 0x72, 0x09, 0x32, 0x54, 0x71, 0x51, 0x30,
			  0x43);
	dsi_dcs_write_seq(dsi, 0xb2, 0x00, 0x80, 0x64, 0x0b, 0x06, 0x2f);
	dsi_dcs_write_seq(dsi, 0xb4,
			  0x1c, 0x78, 0x1c, 0x78, 0x1c, 0x78, 0x01, 0x05, 0xff,
			  0x97, 0x00, 0x3f, 0x1c, 0x78, 0x1c, 0x78, 0x1c, 0x78,
			  0x01, 0x05, 0xff);
	dsi_dcs_write_seq(dsi, 0xd3,
			  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x32,
			  0x10, 0x03, 0x00, 0x03, 0x32, 0x13, 0xc0, 0x00, 0x00,
			  0x32, 0x10, 0x08, 0x00, 0x00, 0x37, 0x04, 0x05, 0x05,
			  0x37, 0x05, 0x05, 0x47, 0x0e, 0x40);
	dsi_dcs_write_seq(dsi, 0xd5,
			  0x18, 0x18, 0x18, 0x18, 0x00, 0x01, 0x02, 0x03, 0x04,
			  0x05, 0x06, 0x07, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
			  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
			  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
			  0x19, 0x19, 0x19, 0x19, 0x20, 0x21, 0x22, 0x23);
	dsi_dcs_write_seq(dsi, 0xd6,
			  0x18, 0x18, 0x19, 0x19, 0x07, 0x06, 0x05, 0x04, 0x03,
			  0x02, 0x01, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
			  0x18, 0x18, 0x27, 0x26, 0x18, 0x18, 0x18, 0x18, 0x18,
			  0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
			  0x19, 0x19, 0x18, 0x18, 0x23, 0x22, 0x21, 0x20);
	dsi_dcs_write_seq(dsi, 0xcc, 0x0b);
	dsi_dcs_write_seq(dsi, 0xc0, 0x1f, 0x73);
	dsi_dcs_write_seq(dsi, 0xc7, 0x00, 0xc0, 0x40, 0xc0);
	dsi_dcs_write_seq(dsi, 0xb6, 0x3c, 0x3c);
	dsi_dcs_write_seq(dsi, 0xe0,
			  0x00, 0x05, 0x0b, 0x11, 0x12, 0x16, 0x19, 0x17, 0x30,
			  0x40, 0x50, 0x4f, 0x58, 0x69, 0x6f, 0x71, 0x7f, 0x82,
			  0x7e, 0x8d, 0x9e, 0x4f, 0x4f, 0x53, 0x58, 0x5d, 0x67,
			  0x74, 0x7f, 0x00, 0x05, 0x0b, 0x11, 0x12, 0x16, 0x19,
			  0x17, 0x30, 0x40, 0x50, 0x4f, 0x58, 0x69, 0x6f, 0x71,
			  0x7f, 0x82, 0x7e, 0x8d, 0x9e, 0x4f, 0x4f, 0x53, 0x58,
			  0x5d, 0x67, 0x74, 0x7f);
	dsi_dcs_write_seq(dsi, 0xd4, 0x02);

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

static int hx8394_f_bitland_off(struct hx8394_f_bitland *ctx)
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

static int hx8394_f_bitland_prepare(struct drm_panel *panel)
{
	struct hx8394_f_bitland *ctx = to_hx8394_f_bitland(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	if (ctx->prepared)
		return 0;

	hx8394_f_bitland_reset(ctx);

	ret = hx8394_f_bitland_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		return ret;
	}

	ctx->prepared = true;
	return 0;
}

static int hx8394_f_bitland_unprepare(struct drm_panel *panel)
{
	struct hx8394_f_bitland *ctx = to_hx8394_f_bitland(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	if (!ctx->prepared)
		return 0;

	ret = hx8394_f_bitland_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);

	ctx->prepared = false;
	return 0;
}

static const struct drm_display_mode hx8394_f_bitland_mode = {
	.clock = (720 + 150 + 17 + 150) * (1280 + 16 + 4 + 12) * 60 / 1000,
	.hdisplay = 720,
	.hsync_start = 720 + 150,
	.hsync_end = 720 + 150 + 17,
	.htotal = 720 + 150 + 17 + 150,
	.vdisplay = 1280,
	.vsync_start = 1280 + 16,
	.vsync_end = 1280 + 16 + 4,
	.vtotal = 1280 + 16 + 4 + 12,
	.width_mm = 63,
	.height_mm = 111,
};

static int hx8394_f_bitland_get_modes(struct drm_panel *panel,
				      struct drm_connector *connector)
{
	struct drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &hx8394_f_bitland_mode);
	if (!mode)
		return -ENOMEM;

	drm_mode_set_name(mode);

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;
	drm_mode_probed_add(connector, mode);

	return 1;
}

static const struct drm_panel_funcs hx8394_f_bitland_panel_funcs = {
	.prepare = hx8394_f_bitland_prepare,
	.unprepare = hx8394_f_bitland_unprepare,
	.get_modes = hx8394_f_bitland_get_modes,
};

static int hx8394_f_bitland_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct hx8394_f_bitland *ctx;
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
			  MIPI_DSI_MODE_EOT_PACKET |
			  MIPI_DSI_CLOCK_NON_CONTINUOUS;

	drm_panel_init(&ctx->panel, dev, &hx8394_f_bitland_panel_funcs,
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

static int hx8394_f_bitland_remove(struct mipi_dsi_device *dsi)
{
	struct hx8394_f_bitland *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);

	return 0;
}

static const struct of_device_id hx8394_f_bitland_of_match[] = {
	{ .compatible = "lyf,bitland-hx8394" }, // FIXME
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, hx8394_f_bitland_of_match);

static struct mipi_dsi_driver hx8394_f_bitland_driver = {
	.probe = hx8394_f_bitland_probe,
	.remove = hx8394_f_bitland_remove,
	.driver = {
		.name = "panel-hx8394-f-bitland",
		.of_match_table = hx8394_f_bitland_of_match,
	},
};
module_mipi_dsi_driver(hx8394_f_bitland_driver);

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator <fix@me>"); // FIXME
MODULE_DESCRIPTION("DRM driver for hx8394_f hd video bitland mode dsi panel");
MODULE_LICENSE("GPL v2");
