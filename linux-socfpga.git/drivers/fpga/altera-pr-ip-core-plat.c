/*
 * Driver for Altera Partial Reconfiguration IP Core
 *
 * Copyright (C) 2016 Intel Corporation
 *
 * Based on socfpga-a10.c Copyright (C) 2015-2016 Altera Corporation
 *  by Alan Tull <atull@opensource.altera.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "altera-pr-ip-core.h"
#include <linux/module.h>
#include <linux/of_device.h>

static int alt_pr_platform_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	void __iomem *reg_base;
	struct resource *res;

	/* First mmio base is for register access */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	reg_base = devm_ioremap_resource(dev, res);

	if (IS_ERR(reg_base))
		return PTR_ERR(reg_base);

	return alt_pr_probe(dev, reg_base);
}

static int alt_pr_platform_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;

	return alt_pr_remove(dev);
}

static const struct of_device_id alt_pr_of_match[] = {
	{ .compatible = "altr,pr-ip-core", },
	{},
};

MODULE_DEVICE_TABLE(of, alt_pr_of_match);

static struct platform_driver alt_pr_platform_driver = {
	.probe = alt_pr_platform_probe,
	.remove = alt_pr_platform_remove,
	.driver = {
		.name	= "alt_pr_ip_core",
		.of_match_table = alt_pr_of_match,
	},
};

module_platform_driver(alt_pr_platform_driver);
