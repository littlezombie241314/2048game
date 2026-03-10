import SwiftUI

struct RootView: View {
    @EnvironmentObject private var authViewModel: AuthViewModel

    var body: some View {
        if authViewModel.isLoggedIn {
            HomeView()
        } else {
            RegistrationView()
        }
    }
}
