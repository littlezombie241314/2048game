import SwiftUI

struct RegistrationView: View {
    @EnvironmentObject private var authViewModel: AuthViewModel

    @State private var fullName = ""
    @State private var email = ""
    @State private var selectedCountry: SupportedCountry = .china
    @State private var selectedGender: Gender = .female

    var body: some View {
        NavigationStack {
            Form {
                Section("App") {
                    Text("女生送货 / Female Delivery")
                        .font(.headline)
                    Text("Multi-platform women-only delivery service.")
                        .font(.subheadline)
                }

                Section("Platform") {
                    Picker("Target Platform", selection: $authViewModel.selectedPlatform) {
                        ForEach(AppPlatform.allCases) { platform in
                            Text(platform.displayName).tag(platform)
                        }
                    }
                }

                Section("Registration") {
                    TextField("Full Name", text: $fullName)
                    TextField("Email", text: $email)
                        .keyboardType(.emailAddress)
                        .textInputAutocapitalization(.never)

                    Picker("Country", selection: $selectedCountry) {
                        ForEach(SupportedCountry.allCases) { country in
                            Text(country.displayName).tag(country)
                        }
                    }

                    Picker("Gender", selection: $selectedGender) {
                        ForEach(Gender.allCases) { gender in
                            Text(gender.displayName).tag(gender)
                        }
                    }
                }

                if let error = authViewModel.errorMessage {
                    Section {
                        Text(error)
                            .foregroundStyle(.red)
                    }
                }

                Section {
                    Button("Create account") {
                        authViewModel.register(
                            fullName: fullName,
                            email: email,
                            country: selectedCountry,
                            gender: selectedGender,
                            platform: authViewModel.selectedPlatform
                        )
                    }
                    .disabled(fullName.isEmpty || email.isEmpty)
                }
            }
            .navigationTitle("Sign Up")
        }
    }
}
