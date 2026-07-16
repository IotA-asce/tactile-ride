#include <zephyr/logging/log.h>

#include <tactile_ride/power_policy.h>

LOG_MODULE_REGISTER(tactile_power, LOG_LEVEL_INF);

void power_policy_init(void)
{
	LOG_INF("Power policy is intentionally inactive during the Phase 1 bench POC");
}
