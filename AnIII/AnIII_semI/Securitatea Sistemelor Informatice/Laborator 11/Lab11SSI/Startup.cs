using Microsoft.Owin;
using Owin;

[assembly: OwinStartupAttribute(typeof(Lab11SSI.Startup))]
namespace Lab11SSI
{
    public partial class Startup
    {
        public void Configuration(IAppBuilder app)
        {
            ConfigureAuth(app);
        }
    }
}
