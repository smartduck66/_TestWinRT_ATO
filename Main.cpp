//
// Test de WINRT en partant de la vidéo CPPCON 2017 de K. Kerr et S. Jones
// Source amendé : syndication = Ajout des lignes notées *******
// 11 mars 2018 : test concluant de génération d'un exécutable autonome, sans DLL, faisant appel à des APIs Windows sans passer par C++/CX ou C++/CLI
// Caractères spéciaux : [ ]   '\n'   {  }   ||   ~   _     @

#include "pch.h"
#include "std_lib_facilities.h"											// *******



using namespace winrt;

using namespace Windows::Foundation;
using namespace Windows::Web::Syndication;
using namespace Windows::System::Diagnostics;							// ******* 

IAsyncAction Sample()
{
    Uri uri(L"http://kennykerr.ca/feed");
    SyndicationClient client;
    SyndicationFeed feed = co_await client.RetrieveFeedAsync(uri);

    for (SyndicationItem item : feed.Items())
    {
        hstring title = item.Title().Text();

        printf("%ls\n", title.c_str());
    }
}

int main()
{
    init_apartment();

    Sample().get();

	// Implémentation tirée de la vidéo ******************************************
	auto info = SystemDiagnosticInfo::GetForCurrentSystem();				
	auto mem = info.MemoryUsage().GetReport().TotalPhysicalSizeInBytes();	
	auto mem_avail = info.MemoryUsage().GetReport().AvailableSizeInBytes();
	cout << endl << "Memoire physique totale : "<<mem<<" octets, soit "<<mem/1000000000<<" Go"<<endl;
	cout << endl << "Memoire disponible      : " << mem_avail << " octets, soit " << mem_avail / 1000000000 << " Go" << endl;
	cout << endl << "Donc, memoire occupee   : " << mem-mem_avail << " octets, soit " << (mem - mem_avail) / 1000000000 << " Go" << endl<<endl;
	
	keep_window_open();														

}




