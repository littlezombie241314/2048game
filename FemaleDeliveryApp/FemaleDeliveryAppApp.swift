import SwiftUI

@main
struct FemaleDeliveryAppApp: App {
    @StateObject private var authViewModel = AuthViewModel()
    @StateObject private var orderViewModel = OrderViewModel()

    var body: some Scene {
        WindowGroup {
            RootView()
                .environmentObject(authViewModel)
                .environmentObject(orderViewModel)
        }
    }
}
