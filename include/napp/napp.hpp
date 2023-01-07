#pragma once
#include <string>
#include <napp/worker.hpp>

namespace nlc
{
    class napp
    {
        public:
        napp(std::string name = "nlc_app");
        ~napp();
        bool Running();
        void ForceKill();

        private:
        std::string m_lc_name;
        bool m_exit = false;
    };
}