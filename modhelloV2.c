/* modhelloV2.c */
#include <linux/init.h>   /* needed by the macros module_init and exit */
#include <linux/module.h> /* needed by all modules */
#include <linux/kernel.h> /* needed by KERN_ definition*/

static int debug_enable = 0;
module_param(debug_enable, int, 0);
MODULE_PARM_DESC(debug_enable, "Enable debug mode");
static int __init hello_init(void)
{
  printk(KERN_ALERT "Hello from kernel world - V2: Debug mode is %s\n", debug_enable ? "enabled" : "disabled"); 
  return 0; /*0 for success, negative for failure */
}

static void __exit hello_exit(void) 
{
  printk(KERN_ALERT "Goodbye from kernel world - V2\n");
}

module_init(hello_init); /*macro to execute module's initialize routine */
module_exit(hello_exit); /*macro to execute module's exit routine */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CE405");
MODULE_DESCRIPTION("Simple module"); 
MODULE_VERSION("V2");
