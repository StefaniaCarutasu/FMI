using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Web;

namespace RecapExamen.Models
{
    public class AppContext: DbContext
    {
        public AppContext(): base("DBConnectionString") 
        {
            Database.SetInitializer(new MigrateDatabaseToLatestVersion<AppContext,
                RecapExamen.Migrations.Configuration>("DBConnectionString"));
        }

        public DbSet<Article> Articles { get; set; }
        public DbSet<Category> Categories { get; set; }
    }
}